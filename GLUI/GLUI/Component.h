#pragma once

#define _USE_MATH_DEFINES
#include <GL\freeglut.h>
#include <list>
#include "math.h"
#include "../Event/EventRaiser.h"

namespace GLUI {

	struct float2 {
		float x;
		float y;

		float2(float x = 0, float y = 0) {
			this->x = x;
			this->y = y;
		}
		float2 operator+(float2 p) {
			return float2(x + p.x, y + p.y);
		}
		float2 operator-(float2 p) {
			return float2(x - p.x, y - p.y);
		}
	};

	class Color {
	private:
		float R;
		float G;
		float B;
		float A;
	public:
		Color(unsigned char R = 0U, unsigned char G = 0U, unsigned char B = 0U, unsigned char A = 255U) {
			this->R = R / 255.0f;
			this->G = G / 255.0f;
			this->B = B / 255.0f;
			this->A = A / 255.0f;
		}
		float get_r() {
			return this->R;
		}
		float get_g() {
			return this->G;
		}
		float get_b() {
			return this->B;
		}
		float get_a() {
			return this->A;
		}
	};

	class Component : public EventRaiser {
	protected:
		Component* parent;								// Pointer to parent component
		std::list<Component*> children;					// Children components
		static const unsigned char char_width = 9;		// Width of drawable char in pixels
		static const unsigned char char_height = 16;	// Height of drawable char in pixels
		float2 pos;										// Top left corner's position of the component relative to the parent component
		float width;									// Width of the component
		float height;									// Height of the component
		float border_width;								// Border width of the component
		float active_border_width;						// Border width of the component on event
		float default_border_width;						// Default border width of the component
		bool visible;									// Determines if the component is visible (if set to false, no children will be drawn)
		bool highlighted;								// Determines if the component is highlighted (mouse is on the component)
		std::string title;								// Title of the component
		Color background_color;							// Color of the component's background
		Color border_color;								// Color of the component's border
		Color highlight_color;							// Color of the component's background when highlighted

		// x,y coordinates of the top left corner, relative to the parent component, width and height, and border width
		Component(float x = 0, float y = 0, float width = 100, float height = 100, float border_width = 2);
		// Raises events according to the input events
		virtual void handle_event(Event& e);
		// Draws the component
		virtual void draw();
	public:
		// Adds a component
		virtual void add_component(Component* c);
		// Removes a component
		virtual void remove_component(Component* c);
		// Sets the position of the component on screen in pixels relative to the parent component
		virtual void set_position(float x, float y);
		// Sets the position of the component on screen in pixels relative to the parent component
		virtual void set_position(float2 pos);
		// Sets the size of the component on screen in pixels
		virtual void set_size(float width, float height);
		// Sets the width of the border of the component on screen in pixels
		virtual void set_default_border_width(float border_width);
		// Sets the title of the component
		virtual void set_title(std::string title);
		// Sets the background color
		virtual void set_background_color(Color background_color);
		// Sets the background color
		virtual void set_background_color(unsigned char R = 0U, unsigned char G = 0U, unsigned char B = 0U, unsigned char A = 255U);
		// Sets the border color
		virtual void set_border_color(Color background_color);
		// Sets the border color
		virtual void set_border_color(unsigned char R = 0U, unsigned char G = 0U, unsigned char B = 0U, unsigned char A = 255U);
		// Sets the highlight color
		virtual void set_highlight_color(Color background_color);
		// Sets the highlight color
		virtual void set_highlight_color(unsigned char R = 0U, unsigned char G = 0U, unsigned char B = 0U, unsigned char A = 255U);
		// Sets the visibility of the component (if set to false, no children will be drawn)
		virtual void set_visible(bool visible);
		// Gets the position of the component relative to the parent component
		virtual float2 get_position();
		// Gets the absolute position of the component
		virtual float2 get_absolute_position();
		// Gets the width of the component
		virtual float get_width();
		// Gets the height of the component
		virtual float get_height();
		// Gets the border's width of the component
		virtual float get_default_border_width();
		// Gets the background color of the component
		virtual Color get_background_color();
		// Gets the border's color of the component
		virtual Color get_border_color();
		// Gets the highlight color of the component
		virtual Color get_highlight_color();
		// Gets visibility of the component
		virtual bool get_visible();

		// Handles input events (keyboard, mouse)
		// Just create events in the main loop and pass them to the top-level window
		void event_handler(Event& e);
		// Draws the component and it's children components
		// Just call it on a top-level window object, and all children components will be drawn
		virtual void render();
	};

	// x,y coordinates of the top left corner, relative to the parent component, width and height, and border width
	Component::Component(float x, float y, float width, float height, float border_width) {
		this->parent = nullptr;
		this->pos = float2(x, y);
		this->width = width;
		this->height = height;
		this->border_width = border_width;
		this->default_border_width = border_width;
		this->active_border_width = border_width + 2;
		this->visible = true;
		this->highlighted = false;
		this->background_color = Color(100, 100, 100, 200);
		this->border_color = Color(200, 200, 200, 255);
		//this->highlight_color = Color(66, 134, 244, 255);
		this->highlight_color = Color(160, 160, 160, 255);
	}

	// Raises events according to input events
	void Component::handle_event(Event& e) {

	}

	// Draws the component
	void Component::draw() {
		float2 pos = this->get_absolute_position();

		// Draw border
		// Top left quarter-circle
		glColor4f(border_color.get_r(), border_color.get_g(), border_color.get_b(), border_color.get_a());
		glBegin(GL_POLYGON);
		for (int i = 0; i <= border_width; ++i) {
			float t = M_PI + i * M_PI / 2.0f / border_width;
			float r = border_width;
			float x = r*cos(t) + pos.x + border_width;
			float y = r*sin(t) + pos.y + border_width;
			glVertex2f(x, y);
		}
		// Top bar
		glVertex2f(pos.x + border_width, pos.y);
		glVertex2f(pos.x + width - border_width, pos.y);
		// Top right quarter-circle
		for (int i = 0; i <= border_width; ++i) {
			float t = -M_PI / 2.0f + i * M_PI / 2.0f / border_width;
			float r = border_width;
			float x = r*cos(t) + pos.x + width - border_width;
			float y = r*sin(t) + pos.y + border_width;
			glVertex2f(x, y);
		}
		glEnd();
		// Bot right quarter-circle
		glBegin(GL_POLYGON);
		for (int i = 0; i <= border_width; ++i) {
			float t = i * M_PI / 2.0f / border_width;
			float r = border_width;
			float x = r*cos(t) + pos.x + width - border_width;
			float y = r*sin(t) + pos.y + height - border_width;
			glVertex2f(x, y);
		}
		// Bot bar
		glVertex2f(pos.x + width - border_width, pos.y + height);
		glVertex2f(pos.x + border_width, pos.y + height);
		// Bot left quarter-circle
		for (int i = 0; i <= border_width; ++i) {
			float t = M_PI / 2.0f + i * M_PI / 2.0f / border_width;
			float r = border_width;
			float x = r*cos(t) + pos.x + border_width;
			float y = r*sin(t) + pos.y + height - border_width;
			glVertex2f(x, y);
		}
		glEnd();
		// Left bar
		glBegin(GL_QUADS);
		glVertex2f(pos.x, pos.y + border_width);
		glVertex2f(pos.x + border_width, pos.y + border_width);
		glVertex2f(pos.x + border_width, pos.y + height - border_width);
		glVertex2f(pos.x, pos.y + height - border_width);
		// Right bar
		glVertex2f(pos.x + width - border_width, pos.y + border_width);
		glVertex2f(pos.x + width, pos.y + border_width);
		glVertex2f(pos.x + width, pos.y + height - border_width);
		glVertex2f(pos.x + width - border_width, pos.y + height - border_width);
		glEnd();

		//// Draw border
		//glColor4f(1.0, 1.0, 1.0, 1);
		//glBegin(GL_QUADS);
		//glVertex2f(pos.x, pos.y);
		//glVertex2f(pos.x + width, pos.y);
		//glVertex2f(pos.x + width, pos.y + height);
		//glVertex2f(pos.x, pos.y + height);
		//glEnd();

		// Draw background
		if (highlighted) {
			glColor4f(highlight_color.get_r(), highlight_color.get_g(), highlight_color.get_b(), highlight_color.get_a());
		} else {
			glColor4f(background_color.get_r(), background_color.get_g(), background_color.get_b(), background_color.get_a());
		}
		glBegin(GL_QUADS);
		glVertex2f(pos.x + border_width, pos.y + border_width);
		glVertex2f(pos.x + width - border_width, pos.y + border_width);
		glVertex2f(pos.x + width - border_width, pos.y + height - border_width);
		glVertex2f(pos.x + border_width, pos.y + height - border_width);
		glEnd();

		// Draw title
		if (!title.empty()) {
			glColor4f(1, 1, 1, 1);
			glRasterPos2f(pos.x + border_width + 5, pos.y + border_width + char_height);
			glutBitmapString(GLUT_BITMAP_9_BY_15, (const unsigned char*)title.c_str());
		}
	}

	// Adds a component
	void Component::add_component(Component* c) {
		c->parent = this;
		children.push_back(c);
	}

	// Removes a component
	void Component::remove_component(Component* c) {
		children.remove(c);
	}

	// Sets the position of the component on screen in pixels relative to the parent component
	void Component::set_position(float x, float y) {
		this->pos = float2(x, y);
	}

	// Sets the position of the component on screen in pixels relative to the parent component
	void Component::set_position(float2 pos) {
		this->pos = pos;
	}

	// Sets the size of the component on screen in pixels
	void Component::set_size(float width, float height) {
		this->width = width;
		this->height = height;
	}

	// Sets the width of the border of the component on screen in pixels
	void Component::set_default_border_width(float border_width) {
		this->default_border_width = border_width;
		this->border_width = border_width;
		this->active_border_width = border_width + 2;
	}

	// Sets the title of the component
	void Component::set_title(std::string title) {
		this->title = title;
	}

	// Sets the background color
	void Component::set_background_color(Color background_color) {
		this->background_color = background_color;
	}

	// Sets the background color
	void Component::set_background_color(unsigned char R, unsigned char G, unsigned char B, unsigned char A) {
		this->background_color = Color(R, G, B, A);
	}

	// Sets the border color
	void Component::set_border_color(Color background_color) {
		this->border_color = background_color;
	}

	// Sets the border color
	void Component::set_border_color(unsigned char R, unsigned char G, unsigned char B, unsigned char A) {
		this->border_color = Color(R, G, B, A);
	}

	// Sets the highlight color
	void Component::set_highlight_color(Color background_color) {
		this->highlight_color = highlight_color;
	}

	// Sets the highlight color
	void Component::set_highlight_color(unsigned char R, unsigned char G, unsigned char B, unsigned char A) {
		this->highlight_color = Color(R, G, B, A);
	}

	// Sets the visibility of the component (if set to false, no children will be drawn)
	void Component::set_visible(bool visible) {
		this->visible = visible;
		for (auto c : children) {
			c->set_visible(visible);
		}
	}

	// Gets the position of the component relative to the parent component
	float2 Component::get_position() {
		return this->pos;
	}

	// Gets the absolute position of the component
	float2 Component::get_absolute_position() {
		if (this->parent == nullptr) {
			return pos;
		} else {
			return pos + parent->get_absolute_position();
		}
	}

	// Gets the width of the component
	float Component::get_width() {
		return this->width;
	}

	// Gets the height of the component
	float Component::get_height() {
		return this->height;
	}

	// Gets the border's width of the component
	float Component::get_default_border_width() {
		return this->default_border_width;
	}

	// Gets the background color of the component
	Color Component::get_background_color() {
		return this->background_color;
	}

	// Gets the border's color of the component
	Color Component::get_border_color() {
		return this->border_color;
	}

	// Gets the highlight color of the component
	Color Component::get_highlight_color() {
		return this->highlight_color;
	}

	// Gets visibility of the component
	bool Component::get_visible() {
		return this->visible;
	}

	// Handles input events (keyboard, mouse)
	void Component::event_handler(Event& e) {
		this->handle_event(e);
		for (auto c : children) {
			c->event_handler(e);
		}
	}

	// Draws the component and it's children components
	// Just call it on a window object, and all children components will be drawn
	void Component::render() {
		if (visible) {
			glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();								// Save current projection matrix
			glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);	// Transform it to able to draw in pixel coordinates
			glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();								// Save current modelview matrix
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glEnable(GL_BLEND);						// Enable transparency

			this->draw();
			for (auto c : children) {
				c->render();
			}

			glDisable(GL_BLEND);
			glPopMatrix(); glMatrixMode(GL_PROJECTION);
			glPopMatrix(); glMatrixMode(GL_MODELVIEW);
		}
	}

}