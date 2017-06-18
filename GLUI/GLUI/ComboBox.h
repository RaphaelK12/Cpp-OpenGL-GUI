#pragma once

#include "Component.h"
#include "Button.h"
#include "Label.h"
#include "ScrollPanel.h"

namespace GLUI {

	// Combobox with selectable drop down list, that can raise events when selected changes
	class ComboBox : public EventListener, public Component {
	protected:
		Label* lbl_selected;				// Displays the selected value
		Button* btn_drop_down;				// The drop down list drops when pressed, and rolls up when pressed again
		ScrollPanel* scp_list;				// The scrollable drop down panel with the selectable elements
		std::list<Button*> btn_elements;	// The selectable elements from the drop down list

		bool dropped_down;					// Indicates if the drop down list is dropped down
		float element_offset;				// For element addition alignment
		float dropped_down_height;			// Component height when dropped down

		virtual void handle_event(Event& e) override;
		virtual void draw(bool draw_background = true) override;
	public:
		// To listen on the children component's events
		virtual void action_performed(void* sender, Event& e) override;
		// The coordinates of the combo box, the size of the combo box, and the border's width of the combo box
		ComboBox(float x = 0, float y = 0, float width = 100, float height = 20, float border_width = 1);
		// Adds an element to the combo box
		void add_element(std::string text);
		// Removes an element from the combo box (or multiple, if there are multiplte elements with the same name)
		void remove_element(std::string text);
	};

	void ComboBox::handle_event(Event& e) {

	}

	void ComboBox::draw(bool draw_background) {
		if (this->visible) {									// If the combobox is visible
			this->scp_list->set_visible(this->dropped_down);	// The dropdown list is not sure visible
			this->height = this->dropped_down ? this->dropped_down_height : 20;
			this->scp_list->set_draw_background(true);
		}
		Component::draw();
	}

	// To listen on the children component's events
	void ComboBox::action_performed(void* sender, Event& e) {
		if (sender == this->btn_drop_down) {					// If the drop down button
			if (e.button_pressed) {								// Was pressed
				this->dropped_down = !this->dropped_down;		// The list opens if it was closed, and closes of it was opened
				this->set_visible(true);						// So need to refresh the visibility tree
			}
		} else {												// Else
			if (e.button_released) {							// If any button in the drop down list was pressed
				std::string text =
					((Button*)sender)->get_label()->get_text();	// Get the selected item's text
				if (text != this->lbl_selected->get_text()) {	// If the previously selected item differs from the one selected now
					this->lbl_selected->set_text(text);			// Change the text
					e.combobox_changed = true;
					e.combobox_selected = text;
					this->raise_event(this, e);					// Raise an event that the selected item changed
					e.combobox_changed = false;
				}
				this->dropped_down = false;						// The drop down list automatically closes when an item is selected from it
				this->set_visible(true);						// Thus the refresh
			}
		}
	}

	// The coordinates of the combo box, the size of the combo box, and the border's width the of the combo box
	ComboBox::ComboBox(float x, float y, float width, float height, float border_width) : Component(x, y, width, 20, border_width) {
		this->dropped_down = false;
		this->element_offset = 0;
		this->dropped_down_height = height;
		this->background_color = Color(120, 120, 120, 255);		// Default grey color
		this->lbl_selected = new Label("", 0, 0, width - 20, 20);
		this->btn_drop_down = new Button(R"(\/)", width - 20 - border_width / 2, border_width / 2, 20, 20 - border_width);
		this->btn_drop_down->add_event_listener(this);
		//this->scp_list = new ScrollPanel(ScrollPanel::ALIGN::VERTICAL, 0, height-border_width, width, 181, border_width);
		this->scp_list = new ScrollPanel(ScrollPanel::ALIGN::VERTICAL, 0, 20-border_width, width, height - 20 + border_width, border_width);
		this->scp_list->get_scroll_bar()->set_increment(20 + border_width);
		this->scp_list->set_visible(false);
		this->add_component(this->lbl_selected);
		this->add_component(this->btn_drop_down);
		this->add_component(this->scp_list);
	}

	// Adds an element to the combo box
	void ComboBox::add_element(std::string text) {
		Button* btn = new Button(text,
								 this->default_border_width + 2, this->default_border_width + this->element_offset + 2,	// X, y
								 this->width - this->default_border_width*2 - 3 - 20, 20);								// Width, height
		btn->set_wait_time(std::numeric_limits<float>::max());
		btn->add_event_listener(this);
		this->element_offset = this->element_offset + 20 + this->default_border_width;
		this->btn_elements.push_back(btn);
		this->scp_list->add_component(btn);
	}

	// Removes an element from the combo box (or multiple, if there are multiplte elements with the same name)
	void ComboBox::remove_element(std::string text) {
		for (auto c : this->btn_elements) {						// Iterate through all the elements
			if (c->get_label()->get_text() == text) {			// If the texts are matching
				c->remove_event_listener(this);					// Remove the event listener from the combobox
				this->remove_component(c);						// Remove the component from the combobox
				this->btn_elements.remove(c);					// Remove the element from the combobox
				break;
			}
		}
	}

}