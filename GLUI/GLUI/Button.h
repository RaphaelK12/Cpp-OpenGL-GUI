#pragma once

#include "Component.h"
#include "Label.h"
#include "../Stopwatch.h"

namespace GLUI {

	// A button with a label inside, that can raise events when pressed/released
	class Button : public Component {
	protected:
		bool clicked;				// Becomes true when the user clicks on a button, and remains true until the user released the left mouse button
		Label* lbl_text;			// The label inside the button, its aligned mid-mid by default
		Stopwatch watch_wait;		// Timer to watch when should the button start repeating button presses
		Stopwatch watch_repeat;		// Timer to watch when should the button raise the next button press event
		float wait_time;			// Time until repeating button presses after the first button press
		float repeat_time;			// Time between repeated button presses

		// Raises a button pressed event
		virtual void press_button(Event& e);
		// Raises a button released event
		virtual void release_button(Event& e);
		virtual void handle_event(Event& e) override;
		virtual void draw() override;
	public:
		// Label inside the button, the coordinates of the button, the size of the button, and the border's width of the button
		Button(std::string text = "Button", float x = 0, float y = 0, float width = 100, float height = 20, float border_width = 1);
		// Sets the wait time
		void set_wait_time(float wait_time);
		// Sets the repeat time
		void set_repeat_time(float repeat_time);
		// Gets the wait time
		float get_wait_time();
		// Gets the repeat time
		float get_repeat_time();
		// Returns the label
		Label* get_label();
		// Returns the 'clicked' variable
		bool get_clicked();
	};

	// Raises a button pressed event
	void Button::press_button(Event& e) {
		border_width = active_border_width;										// The button press 'animation'
		clicked = true;
		e.button_pressed = true;
		e.button_released = false;
		this->raise_event(this, e);												// Raise an event that the button was pressed
		e.button_pressed = false;
		e.button_released = false;
		this->watch_wait.start();
	}

	// Raises a button released event
	void Button::release_button(Event& e) {
		border_width = default_border_width;											// The button press 'animation' is over, decrease the border's width
		clicked = false;
		e.button_pressed = false;
		e.button_released = true;
		this->raise_event(this, e);														// Raise an event that the button was released
		e.button_pressed = false;
		e.button_released = false;
	}

	void Button::handle_event(Event& e) {
		float2 pos = this->get_absolute_position();											// The absolute position relative to the top-level window
		if (pos.x < e.x && e.x < pos.x + width && pos.y < e.y && e.y < pos.y + height) {	// Check if the mouse was was above the button when the event happened
			if (visible) {																	// Check if visible, because one does not simply press a button if it's invisible
				this->highlighted = true;													// Highlight the button if the mouse is above the button
				if (e.mouse_left && e.mouse_pressed & !clicked) {							// Check if the user clicked on the button with the left mouse button
					this->press_button(e);
				} else if (e.mouse_left_down) {
					if (this->watch_wait.is_running()) {
						if (this->watch_wait.get_elapsed_time() > this->wait_time-this->repeat_time) {
							if (this->watch_repeat.is_running()) {
								if (this->watch_repeat.get_elapsed_time() > this->repeat_time) {
									this->release_button(e);
									this->press_button(e);
									this->watch_repeat.stop();
									this->watch_repeat.start();
								}
							} else {
								this->watch_repeat.start();
							}
						}
					}
				} else {
					this->watch_wait.stop();
					this->watch_repeat.stop();
				}
			}
		} else {
			this->watch_wait.stop();
			this->watch_repeat.stop();
			if (!clicked) {
				this->highlighted = false;														// Disable the highligh when the mouse is not above the button, and the button is not currently being pressed
			}
		}
		if (e.mouse_left && e.mouse_released && clicked) {									// Check if the user released the left mouse button
			this->release_button(e);
		}
	}

	void Button::draw() {
		lbl_text->set_position(default_border_width, default_border_width);					// Dynamically set the label's position to match the button's position
		lbl_text->set_size(width - default_border_width, height - default_border_width);	// Dynamically set the label's size to match the button's size

		Component::draw();																	// Draw the base component
	}

	// Label inside the button, the coordinates of the button, the size of the button, and the border's width of the button
	Button::Button(std::string text, float x, float y, float width, float height, float border_width) : Component(x, y, width, height, border_width) {
		this->wait_time = 0.5;
		this->repeat_time = 0.10;

		this->background_color = Color(120, 120, 120, 255);
		this->clicked = false;
		this->lbl_text = new Label(text);
		this->add_component(this->lbl_text);
	}

	void Button::set_wait_time(float wait_time) {
		this->wait_time = std::max(wait_time, 0.25f);
	}

	void Button::set_repeat_time(float repeat_time) {
		this->repeat_time = std::max(repeat_time, 0.0f);
	}

	float Button::get_wait_time() {
		return this->wait_time;
	}

	float Button::get_repeat_time() {
		return this->repeat_time;
	}

	// Returns the label
	Label* Button::get_label() {
		return lbl_text;
	}

	// Returns the 'clicked' variable
	bool Button::get_clicked() {
		return clicked;
	}

}