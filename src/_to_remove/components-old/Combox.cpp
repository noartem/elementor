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
        this->element = this->tooltipElement
            ->setGap(4)
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
                }));
    }

    std::shared_ptr<Element> Combox::renderTip() {
        float availableHeight = (this->window->getSize().height - this->rect.position.y) / this->ctx->getPixelScale() - 64;
        float maxHeight = 300;
        float minHeight = 0;
        float tipHeight = std::max(std::min(availableHeight, maxHeight), minHeight);
        float tipWidth = this->rect.size.width / this->ctx->getPixelScale() - 8;

        return rounded()
            ->setRadius(4)
            ->setChild(background()
            ->setColor("#FFFFFF")
            ->setChild(border()
                ->setWidth(4)
                ->setColor("#7FB6A4")
                ->setRadius(4)
                ->setChild(height()
                    ->setHeight(tipHeight)
                    ->setChild(width()
                        ->setWidth(tipWidth)
                        ->setChild(scroll()
                            ->setChild(this->renderOptions()))))));
    }

    std::shared_ptr<Element> Combox::renderOptions() {
        auto columnElement = column();

        for (auto option : this->options) {
            std::shared_ptr<Background> backgroundElement = background();
            columnElement
                ->appendChild(backgroundElement
                    ->setColor("#FFFFFF")
                    ->setChild(withCursor()
                        ->setCursorShape(CursorShape::Hand)
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
                            }))));
        }

        return columnElement;
    }

    void Combox::setActive(bool newValue) {
        if (newValue) {
            this->tooltipElement->setTip(this->renderTip());
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
        return shared_from_this();
    }

    std::shared_ptr<Combox> Combox::addOption(const std::tuple<std::string, std::string>& option) {
        this->options.push_back(option);
        return shared_from_this();
    }

    std::shared_ptr<Combox> Combox::addOption(const std::string &optionValue, const std::string &optionLabel) {
        this->options.emplace_back(optionValue, optionLabel);
        return shared_from_this();
    }

    void Combox::removeOption(size_t i) {
        this->options.erase(this->options.begin() + i);
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