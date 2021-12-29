#include <string>
#include <iostream>

#include "window.h"
#include "input.h"
#include "button.h"
#include "grid.h"
#include "lineBreak.h"

namespace GuiElements {

Window::Window() {
    body = new Container(Geometry::Point(0.0f, 0.0f), Geometry::Rectangle::screenWidth, Geometry::Rectangle::screenHeight);
	rotationXMag = 0.0f;
	rotationYMag = 0.0f;
	prevRotationXMag = 0.0f;
	prevRotationYMag = 0.0f;
}

Window::~Window() {
    delete body;
}

Element* Window::getElement(tinyxml2::XMLElement* elem) {
	Element* returned = nullptr;
	std::string name(elem->Name());
	if (name == "container")
		returned = new Container();
	else if (name == "input") {
		returned = new Input();
		returned->text.scale = 0.7f;
	}
	else if (name == "button") {
		returned = new Button();
	} 
	else if (name == "grid") {
		returned = new Grid();
	}
	else if (name == "br") {
		return LineBreak::getInstance();
	}

	if (returned != nullptr) {
		// TODO: add auto values
		// TODO: add checking
		// TODO: bug when adding text to input from xml file, related to textWidth
		
		// Add text
		auto nodeIterator = elem->FirstChild();
		if (nodeIterator) {
			auto val = nodeIterator->ToText();
			if (val)
				returned->text = Text(std::move(std::string(val->Value())), Geometry::Color{ 0.5f, 0.8f, 0.9f }, 0.5f);
		}

		// default values
		float colorDef[3] = { 0.0f, 0.525f, 0.592f };
		returned->rect.color = colorDef;
		returned->rect.setXY(0.0f, 0.0f);

		auto h = elem->Attribute("height");
		auto w = elem->Attribute("width");
		auto id = elem->Attribute("id");
		auto color = elem->Attribute("color");


		if (w)
			returned->rect.width = std::stoi(w);
		else
			returned->calculateWidth();
		if (h)
			returned->rect.height = std::stoi(h);
		else
			returned->calculateHeight();

		if (color) returned->rect.color = Geometry::Color(color);
		if (id) returned->id = id;
	}
	return returned;
}

void Window::addDoc(tinyxml2::XMLNode& doc, Container* body) {
    auto childIterator = doc.FirstChildElement();
    while (childIterator != nullptr)
    {
		Element* childElement = getElement(childIterator);
		if (childElement == nullptr)
			throw std::string("Not a valid type ") + childIterator->Name();
		std::cout << "adding " << childIterator->Name() << std::endl;
		body->addAutoArrange(childElement);
		std::cout << childElement->rect.getX() << "," << childElement->rect.getY() << std::endl;

		if (childElement->isContainer())
        	addDoc(*childIterator, (Container*)childElement);
		else if (childIterator->FirstChildElement()) {
			// if has children in xml but not a container, throw error
			// TODO: delete allocated space for all children of body (after main?)
			throw "Non container element containing elements";
		}

		childIterator = childIterator->NextSiblingElement();
	}
}

void Window::deleteChildren(Container* body) {
	if (body != nullptr) {
		for (auto &&elem : body->elements)
		{
			if (elem->isContainer())
				deleteChildren((Container*)elem);
			if (elem != LineBreak::getInstance())
				delete elem;
		}
		body->elements.clear();
	}
}

void Window::fromDoc(std::string&& docPath) {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("document.xml");
	if (doc.Error())
		std::cout << "error loading xml file\n";

	Window::addDoc(doc, this->body);
}

void Window::deleteChildren() {
	Window::deleteChildren(this->body);
}

}; // namespace GuiElements