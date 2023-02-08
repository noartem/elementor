//
// Created by noartem on 05.02.2023.
//

#include "Combox.h"
#include "WithCursor.h"
#include "Scroll.h"

namespace elementor::components {
    std::shared_ptr<Combox> combox() {
        return std::make_shared<Combox>();
    }

    Combox::Combox() {
        this->paragraphElement = paragraph();
        this->textElement = text();
        this->borderElement = border();

        this->tooltipElement = tooltip();
        this->tipWidthElement = width();
        this->optionsColumnElement = column();

        this->element = this->tooltipElement
            ->setChild(clickable()
                ->setChild(withCursor()
                    ->setCursorShape(CursorShape::Hand)
                    ->setChild(background()
                        ->setColor("#FFFFFF")
                        ->setChild(borderElement
                            ->setWidth(4)
                            ->setColor("#DEEDE6")
                            ->setRadius(4)
                            ->setChild(rounded()
                                ->setRadius(4)
                                ->setChild(padding()
                                    ->setPaddings(8)
                                    ->setChild(height()
                                        ->setHeight(15)
                                        ->setChild(paragraphElement
                                            ->appendChild(textElement
                                                ->setFontColor("#3F4944")
                                                ->setFontSize(16)
                                                ->setFontWeight(500)
                                                ->setFontFamily("Fira Code")
                                                ->setText(this->placeholder)))))))))
                ->onClick([this] () {
                    this->toggleActive();
                }))
            ->setTip(rounded()
                ->setRadius(4)
                ->setChild(background()
                ->setColor("#FFFFFF")
                ->setChild(border()
                    ->setWidth(4)
                    ->setColor("#7FB6A4")
                    ->setRadius(4)
                    ->setChild(height()
                        ->setHeight(300)
                        ->setChild(this->tipWidthElement
                            ->setWidth(this->rect.size.width)
                            ->setChild(scroll()
                                ->setChild(this->optionsColumnElement)))))));
    }

    void Combox::updateOptionsElement() {
        if (this->optionsColumnElement == nullptr) {
            return;
        }

        this->optionsColumnElement->clearChildren();

        for (auto option : this->options) {
            std::shared_ptr<Background> backgroundElement = background();
            this->optionsColumnElement
                ->appendChild(backgroundElement
                    ->setColor("#FFFFFF")
                    ->setChild(hoverable()
                        ->setChild(clickable()
                            ->setChild(padding()
                                ->setPaddings(8)
                                ->setChild(height()
                                    ->setHeight(15)
                                    ->setChild(paragraph()
                                        ->appendChild(text()
                                            ->setFontColor("#3F4944")
                                            ->setFontSize(16)
                                            ->setFontWeight(500)
                                            ->setFontFamily("Fira Code")
                                            ->setText(std::get<1>(option))))))
                            ->onClick([this, option] () {
                                this->setValue(option);
                            }))
                        ->onEnter([backgroundElement] () {
                            backgroundElement->setColor("#DCEBE4");
                        })
                        ->onLeave([backgroundElement] () {
                            backgroundElement->setColor("#FFFFFF");
                        })));
        }
    }

    void Combox::setActive(bool newValue) {
        if (newValue) {
            this->tipWidthElement->setWidth(this->rect.size.width);
        }

        this->tooltipElement->setActive(newValue);
    }

    void Combox::toggleActive() {
        this->setActive(!this->getActive());
    }

    bool Combox::getActive() const {
        return this->tooltipElement->getActive();
    }

    std::shared_ptr<Combox> Combox::setValue(std::tuple<std::string, std::string> option) {
        this->textElement->setText(std::get<1>(option));
        this->paragraphElement->forceUpdate();

        this->setActive(false);

        auto oldValue = this->value;
        this->value = std::get<0>(option);
        if (this->value != oldValue && this->callbackChange) {
            this->callbackChange(this->value);
        }

        return shared_from_this();
    }

    std::shared_ptr<Combox> Combox::setValue(const std::string &optionValue) {
        for (auto option: this->options) {
            if (std::get<0>(option) == optionValue) {
                this->setValue(option);
                break;
            }
        }
        return shared_from_this();
    }

    std::string Combox::getValue() const {
        return this->value;
    }

    std::shared_ptr<Combox> Combox::setOptions(std::vector<std::tuple<std::string, std::string>> newOptions) {
        this->options = std::move(newOptions);
        this->updateOptionsElement();
        return shared_from_this();
    }

    std::shared_ptr<Combox> Combox::addOption(const std::tuple<std::string, std::string>& option) {
        this->options.push_back(option);
        this->updateOptionsElement();
        return shared_from_this();
    }

    std::shared_ptr<Combox> Combox::addOption(const std::string &optionValue, const std::string &optionLabel) {
        this->options.emplace_back(optionValue, optionLabel);
        this->updateOptionsElement();
        return shared_from_this();
    }

    void Combox::removeOption(size_t i) {
        this->options.erase(this->options.begin() + i);
        this->updateOptionsElement();
    }

    void Combox::removeOption(const std::string &optionValue) {
        for (unsigned int i = 0; i < this->options.size(); ++i) {
            if (std::get<0>(this->options[i]) == optionValue) {
                this->removeOption(i);
                return;
            }
        }
    }

    void Combox::removeOption(const std::tuple<std::string, std::string> &option) {
        for (unsigned int i = 0; i < this->options.size(); ++i) {
            if (this->options[i] == option) {
                this->removeOption(i);
                return;
            }
        }
    }

    std::vector<std::tuple<std::string, std::string>> Combox::getOptions() const {
        return this->options;
    }

    size_t Combox::getOptionsSize() const {
        return this->options.size();
    }

    std::tuple<std::string, std::string> Combox::getOption(size_t i) const {
        return this->options[i];
    }

    size_t Combox::optionIndex(const std::tuple<std::string, std::string> &option) const {
        for (size_t i = 0; i < this->options.size(); ++i) {
            if (this->options[i] == option) {
                return i;
            }
        }
        return -1;
    }

    size_t Combox::optionIndex(const std::string &optionValue) const {
        for (size_t i = 0; i < this->options.size(); ++i) {
            if (std::get<0>(this->options[i]) == optionValue) {
                return i;
            }
        }
        return -1;
    }

    std::shared_ptr<Combox> Combox::onChange(std::function<void(std::string value)> callback) {
        this->callbackChange = std::move(callback);
        return shared_from_this();
    }

    std::shared_ptr<Combox> Combox::setPlaceholder(const std::string &newPlaceholder) {
        this->placeholder = newPlaceholder;
        this->textElement->setText(this->placeholder);
        this->paragraphElement->forceUpdate();
        return shared_from_this();
    }

    std::string Combox::getPlaceholder() const {
        return this->placeholder;
    }
}