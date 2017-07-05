#include <nimble/common.h>
#include <nimble/app.h>
#include <nimble/layoutloader.h>
#include <nimble/ini.h>
#include <nimble/widgetselector.h>

#include <nimble/widgets/rect.h>
#include <nimble/widgets/button.h>
#include <nimble/widgets/label.h>

#include <nimble/content/nodes/stylenode.h>

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
#include <irrXML.h>

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
	lay_set_size_xy(m_layout, root, m_bufferSize.x / pixelScale, m_bufferSize.y / pixelScale);

	if (m_root != nullptr) {
		m_root->DoLayout(m_layout, root);
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

	if (m_root != nullptr) {
		m_root->Draw(m_nvg);
	}

	nvgEndFrame(m_nvg);

	glfwSwapBuffers(m_window);
}

void na::Application::Frame()
{
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
	return m_bufferSize.x / m_windowSize.x;
}

void na::Application::Selector(const s2::string &query, s2::list<Widget*> &out)
{
	WidgetSelectorNode node;
	node.Parse(query);
	node.Match(m_root, out);
}

void na::Application::SetRoot(Widget* root)
{
	if (m_root != root) {
		InvalidateLayout();
	}
	m_root = root;
}

void na::Application::LoadLayout(const s2::string &filename)
{
	irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader(filename);
	if (xml == nullptr) {
		printf("Couldn't open %s\n", (const char*)filename);
		return;
	}

	LayoutLoader loader(this, xml);
	SetRoot(loader.Load());

	delete xml;
}

void na::Application::LoadStyle(const s2::string &filename)
{
	Ini ini(filename);
	for (IniSection &section : ini.Sections) {
		s2::list<na::Widget*> widgets;
		Selector(section.Name, widgets);

		for (na::Widget* w : widgets) {
			StyleNode node(&section);
			w->Load(node);
		}
	}
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

void na::Application::CallbackCursorPosition(const glm::ivec2 &point)
{
	for (int i = (int)m_hoveringWidgets.len() - 1; i >= 0; i--) {
		Widget* w = m_hoveringWidgets[i];
		if (!w->IsHovering() || w->Contains(point)) {
			continue;
		}

		w->OnMouseLeave();
		m_hoveringWidgets.remove(i);
	}

	if (m_root == nullptr) {
		return;
	}

	HandleHoverWidgets(m_root, point);
}

void na::Application::CallbackMouseButton(int button, int action, int mods)
{
	if (m_hoveringWidgets.len() == 0) {
		return;
	}

	Widget* w = m_hoveringWidgets[m_hoveringWidgets.len() - 1];
	if (action == GLFW_PRESS) {
		w->OnMouseDown(button);
	} else if (action == GLFW_RELEASE) {
		w->OnMouseUp(button);
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
