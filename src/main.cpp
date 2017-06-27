#include <cstdio>

#include <s2list.h>

#include <GL/glew.h>
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

static bool _invalidated = true;

class Button
{
public:
	int m_x, m_y;
	int m_width, m_height;
	bool m_hovering;
	bool m_down;

public:
	Button(int x, int y, int width = 120, int height = 30)
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_hovering = false;
		m_down = false;
	}

	~Button()
	{
	}

	bool Contains(int x, int y)
	{
		return (x >= m_x && x < m_x + m_width) && (y >= m_y && y < m_y + m_height);
	}

	void Draw(NVGcontext* vg)
	{
		nvgBeginPath(vg);
		nvgRect(vg, m_x, m_y, m_width, m_height);
		if (m_hovering) {
			if (m_down) {
				nvgFillColor(vg, nvgRGBA(255, 127, 0, 255));
			} else {
				nvgFillColor(vg, nvgRGBA(255, 255, 127, 255));
			}
		} else {
			nvgFillColor(vg, nvgRGBA(0, 127, 255, 255));
		}
		nvgFill(vg);
	}

	void MouseEnter()
	{
		m_hovering = true;
		m_down = false;
		_invalidated = true;
	}

	void MouseLeave()
	{
		m_hovering = false;
		m_down = false;
		_invalidated = true;
	}

	void MouseDown(int button)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			m_down = true;
			_invalidated = true;
		}
	}

	void MouseUp(int button)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (m_down) {
				Click();
			}
			m_down = false;
			_invalidated = true;
		}
	}

	void Click()
	{
		printf("Button was clicked!\n");
		m_x += 10;
		_invalidated = true;
	}
};

static s2::list<Button*> _buttons;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	for (Button* b : _buttons) {
		if (!b->Contains((int)xpos, (int)ypos)) {
			if (b->m_hovering) {
				b->MouseLeave();
			}
			continue;
		}
		if (!b->m_hovering) {
			b->MouseEnter();
		}
	}
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	for (Button* b : _buttons) {
		if (!b->m_hovering) {
			continue;
		}
		if (action == GLFW_PRESS) {
			b->MouseDown(button);
		} else if (action == GLFW_RELEASE) {
			b->MouseUp(button);
		}
	}
}

int main()
{
	if (!glfwInit()) {
		printf("Glfw failed\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "Nimble App", nullptr, nullptr);
	if (window == nullptr) {
		printf("No windpw\n");
		glfwTerminate();
		return -1;
	}

	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("Glew failed\n");
		glfwTerminate();
		return -1;
	}
	glGetError();

	NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	if (vg == nullptr) {
		printf("Nvg failed\n");
		glfwTerminate();
		return -1;
	}

	_buttons.add(new Button(100, 100));
	_buttons.add(new Button(100, 150));
	_buttons.add(new Button(100, 200));
	_buttons.add(new Button(100, 250));

	while (!glfwWindowShouldClose(window)) {
		if (_invalidated) {
			static int _frameCount = 0;
			printf("Begin frame %d\n", _frameCount++);

			glClear(GL_COLOR_BUFFER_BIT);

			nvgBeginFrame(vg, 1024, 768, 1.0f);

			for (Button* b : _buttons) {
				b->Draw(vg);
			}

			nvgEndFrame(vg);

			glfwSwapBuffers(window);
			_invalidated = false;
		}

		glfwWaitEvents();
	}
	glfwTerminate();

	return 0;
}
