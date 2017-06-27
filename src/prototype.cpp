#include <cstdio>

#include <s2list.h>

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

int main()
{
	/*
	lay_context lay;
	lay_init_context(&lay);

	lay_id root = lay_item(&lay);
	lay_set_size_xy(&lay, root, 1024, 768);
	lay_set_contain(&lay, root, LAY_ROW);

	lay_id master_list = lay_item(&lay);
	lay_set_size_xy(&lay, master_list, 400, 0);
	lay_set_behave(&lay, master_list, LAY_VFILL);
	lay_set_contain(&lay, master_list, LAY_COLUMN);
	lay_insert(&lay, root, master_list);

	lay_id content_view = lay_item(&lay);
	lay_set_behave(&lay, content_view, LAY_FILL);

	lay_run_context(&lay);
	lay_vec4 master_list_rect = lay_get_rect(&lay, master_list);
	lay_vec4 content_view_rect = lay_get_rect(&lay, content_view);

	printf("master: %d,%d -- %d,%d\n", master_list_rect[0], master_list_rect[1], master_list_rect[2], master_list_rect[3]);
	printf("content: %d,%d -- %d,%d\n", content_view_rect[0], content_view_rect[1], content_view_rect[2], content_view_rect[3]);

	//lay_reset_context(&lay);
	lay_destroy_context(&lay);

	return 0;
	*/

	_buttons.add(new Button(100, 100));
	_buttons.add(new Button(100, 150));
	_buttons.add(new Button(100, 200));
	_buttons.add(new Button(100, 250));

	return 0;
}
