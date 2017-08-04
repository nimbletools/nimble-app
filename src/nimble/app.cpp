#include <nimble/common.h>
#include <nimble/app.h>

#include <nimble/widgets/rect.h>
#include <nimble/widgets/button.h>
#include <nimble/widgets/label.h>
#include <nimble/widgets/text.h>

#include <nimble/utils/ini.h>

#include <GL/glew.h>
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

#include <nanovg.h>
#define NANOVG_GL3
#include <nanovg_gl.h>

#include <layout.h>

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	na::Application* app = (na::Application*)glfwGetWindowUserPointer(window);
	if (app == nullptr) {
		return;
	}
	app->CallbackCursorPosition(glm::ivec2((int)xpos, (int)ypos));
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	na::Application* app = (na::Application*)glfwGetWindowUserPointer(window);
	if (app == nullptr) {
		return;
	}
	app->CallbackMouseButton(button, action, mods);
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
	na::Application* app = (na::Application*)glfwGetWindowUserPointer(window);
	if (app == nullptr) {
		return;
	}
	app->CallbackWindowResized(width, height);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	na::Application* app = (na::Application*)glfwGetWindowUserPointer(window);
	if (app == nullptr) {
		return;
	}
	app->CallbackFramebufferResized(width, height);
}

na::Application::Application()
	: Content(this)
{
	m_windowSize = glm::ivec2(1024, 768);

	InitializeLayout();

	//TODO: Move these
	WidgetFactories.add("rect", [this]() {
		return new RectWidget(this);
	});
	WidgetFactories.add("hbox", [this]() {
		RectWidget* ret = new RectWidget(this);
		ret->SetLayoutDirection(WidgetDirection::Horizontal);
		return ret;
	});
	WidgetFactories.add("vbox", [this]() {
		RectWidget* ret = new RectWidget(this);
		ret->SetLayoutDirection(WidgetDirection::Vertical);
		return ret;
	});
	WidgetFactories.add("label", [this]() {
		return new LabelWidget(this);
	});
	WidgetFactories.add("button", [this]() {
		ButtonWidget* ret = new ButtonWidget(this);
		ret->SetLayoutAnchor(AnchorFillH);
		ret->SetSize(glm::ivec2(0, 26));
		return ret;
	});
	WidgetFactories.add("text", [this]() {
		return new TextWidget(this);
	});
}

na::Application::~Application()
{
	CleanupLayout();
	CleanupRendering();
}

void na::Application::Run()
{
	InitializeRendering();
	InitializeWindow();

	OnLoad();

	while (!glfwWindowShouldClose(m_window)) {
		Frame();

		if (IsInvalidated()) {
			glfwPollEvents();
		} else {
			glfwWaitEvents(); // interrupt using glfwPostEmptyEvent
		}
	}
}

void na::Application::DoLayout()
{
	static int _layoutCount = 0;
	printf("Layout %d\n", _layoutCount++);

	float pixelScale = GetPixelScale();

	lay_reset_context(m_layout);
	lay_id root = lay_item(m_layout);
	lay_set_size_xy(m_layout, root, (lay_scalar)(m_bufferSize.x / pixelScale), (lay_scalar)(m_bufferSize.y / pixelScale));

	for (int i = m_pages.len() - 1; i >= 0; i--) {
		PageWidget* page = m_pages[i];
		page->DoLayout(m_layout, root);
		if (!page->DrawBehind() && !page->InputBehind()) {
			break;
		}
	}

	lay_run_context(m_layout);
}

void na::Application::Draw()
{
	static int _renderCount = 0;
	printf("Render %d\n", _renderCount++);

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, m_bufferSize.x, m_bufferSize.y);

	nvgBeginFrame(m_nvg, m_bufferSize.x, m_bufferSize.y, 1.0f);

	float pixelScale = GetPixelScale();
	nvgScale(m_nvg, pixelScale, pixelScale);

	int pageStartIndex = m_pages.len() - 1;
	for (; pageStartIndex > 0; pageStartIndex--) {
		if (!m_pages[pageStartIndex]->DrawBehind()) {
			break;
		}
	}
	for (int i = pageStartIndex; i < (int)m_pages.len(); i++) {
		PageWidget* page = m_pages[i];
		page->Draw(m_nvg);
	}

	nvgEndFrame(m_nvg);

	glfwSwapBuffers(m_window);
}

void na::Application::Frame()
{
	HandlePageQueue();

	if (m_invalidatedLayout) {
		m_invalidatedLayout = false;
		DoLayout();
		m_invalidatedRendering = true;
	}

	if (m_invalidatedRendering) {
		m_invalidatedRendering = false;
		Draw();
	}
}

void na::Application::OnLoad()
{
}

void na::Application::SetWindowSize(const glm::ivec2 &size)
{
	if (m_windowSize != size) {
		InvalidateLayout();
	}

	m_windowSize = size;
	glfwSetWindowSize(m_window, size.x, size.y);
	glfwGetFramebufferSize(m_window, &m_bufferSize.x, &m_bufferSize.y);
}

float na::Application::GetPixelScale()
{
	return m_bufferSize.x / (float)m_windowSize.x;
}

void na::Application::HandlePageQueue()
{
	for (PageAction &pa : m_pageQueue) {
		if (pa.m_type == PageActionType::Push) {
			InvalidateHoverWidgets();
			m_pages.push() = pa.m_page;
			InvalidateLayout();

		} else if (pa.m_type == PageActionType::Pop) {
			InvalidateHoverWidgets();
			delete m_pages.pop();
			InvalidateLayout();
		}
	}
	m_pageQueue.clear();
}

void na::Application::PushPage(PageWidget* page)
{
	m_pageQueue.add(PageAction(PageActionType::Push, page));
}

void na::Application::PopPage()
{
	if (m_pages.len() == 1) {
		printf("Can't pop page if there is only 1 page left!\n");
		return;
	}
	m_pageQueue.add(PageAction(PageActionType::Pop));
}

bool na::Application::IsInvalidated()
{
	return m_invalidatedLayout || m_invalidatedRendering;
}

void na::Application::InvalidateLayout()
{
	m_invalidatedLayout = true;
}

void na::Application::InvalidateRendering()
{
	m_invalidatedRendering = true;
}

void na::Application::HandleHoverWidgets(Widget* w, const glm::ivec2 &point)
{
	if (!w->Contains(point)) {
		return;
	}

	if (!w->IsHovering()) {
		m_hoveringWidgets.add(w);
		w->OnMouseEnter();
	}

	for (Widget* child : w->GetChildren()) {
		HandleHoverWidgets(child, point);
	}
}

void na::Application::InvalidateHoverWidgets()
{
	for (auto w : m_hoveringWidgets) {
		w->OnMouseLeave();
	}
	m_hoveringWidgets.clear();
}

void na::Application::CallbackCursorPosition(const glm::ivec2 &point)
{
	m_lastCursorPos = point;

	for (int i = (int)m_hoveringWidgets.len() - 1; i >= 0; i--) {
		Widget* w = m_hoveringWidgets[i];
		if (!w->IsHovering() || w->Contains(point)) {
			w->OnMouseMove(w->ToRelativePoint(point));
			continue;
		}

		w->OnMouseLeave();
		m_hoveringWidgets.remove(i);
	}

	for (int i = m_pages.len() - 1; i >= 0; i--) {
		PageWidget* page = m_pages[i];
		HandleHoverWidgets(page, point);
		if (!page->InputBehind()) {
			break;
		}
	}
}

void na::Application::CallbackMouseButton(int button, int action, int mods)
{
	if (m_hoveringWidgets.len() == 0) {
		return;
	}

	Widget* w = m_hoveringWidgets[m_hoveringWidgets.len() - 1];
	if (action == GLFW_PRESS) {
		w->OnMouseDown(button, w->ToRelativePoint(m_lastCursorPos));
	} else if (action == GLFW_RELEASE) {
		w->OnMouseUp(button, w->ToRelativePoint(m_lastCursorPos));
	}
}

void na::Application::CallbackWindowResized(int width, int height)
{
	InvalidateLayout();

	m_windowSize = glm::ivec2(width, height);
}

void na::Application::CallbackFramebufferResized(int width, int height)
{
	if (m_bufferSize.x == width && m_bufferSize.y == height) {
		return;
	}

	InvalidateLayout();

	m_bufferSize = glm::ivec2(width, height);
}

void na::Application::InitializeLayout()
{
	m_layout = new lay_context;
	lay_init_context(m_layout);
	m_initializedLayout = true;
}

void na::Application::InitializeRendering()
{
	if (!glfwInit()) {
		printf("Glfw failed\n");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	m_initializedRendering = true;
}

void na::Application::InitializeWindow()
{
	m_window = glfwCreateWindow(m_windowSize.x, m_windowSize.y, "Nimble App", nullptr, nullptr);
	if (m_window == nullptr) {
		printf("No window\n");
		CleanupRendering();
		return;
	}

	glfwGetFramebufferSize(m_window, &m_bufferSize.x, &m_bufferSize.y);

	glfwSetWindowUserPointer(m_window, this);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetWindowSizeCallback(m_window, window_size_callback);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("Glew failed\n");
		CleanupRendering();
		return;
	}
	glGetError();

	m_nvg = nvgCreateGL3(/*NVG_ANTIALIAS | */NVG_STENCIL_STROKES);
	if (m_nvg == nullptr) {
		printf("Nvg failed\n");
		CleanupRendering();
		return;
	}

	m_initializedWindow = true;
}

void na::Application::CleanupLayout()
{
	if (!m_initializedLayout) {
		return;
	}

	lay_destroy_context(m_layout);
	delete m_layout;
	m_layout = nullptr;

	m_initializedLayout = false;
}

void na::Application::CleanupRendering()
{
	if (!m_initializedRendering) {
		return;
	}

	glfwTerminate();

	m_initializedRendering = false;
	m_initializedWindow = false;
}
