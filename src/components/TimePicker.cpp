//
// Created by noartem on 10.02.2023.
//

#include "TimePicker.h"
#include "WithCursor.h"

namespace elementor::components {
    std::shared_ptr<TimePicker> timePicker() {
        return std::make_shared<TimePicker>();
    }

    TimePicker::TimePicker() {
        this->timeTemplateRow = row();
        this->element = background()
            ->setColor("#FFFFFF")
            ->setChild(border()
                ->setWidth(4)
                ->setColor("#DEEDE6")
                ->setRadius(4)
                ->setChild(rounded()
                    ->setRadius(4)
                    ->setChild(padding()
                        ->setPaddings(2)
                        ->setChild(height()
                            ->setHeight(23)
                                ->setChild(alignHeight()
                                    ->setCoef(0.5, 0.5)
                                    ->setChild(this->timeTemplateRow
                                        ->setSpacing(4)))))));

        this->updateTemplate("DMYhm");
        this->updateTime(now_tm());
    }

    void TimePicker::updateTimeTemplateElement() {
        this->timeTemplateRow->clearChildren();

        for (const auto &element : this->timeTemplate) {
            if (!this->timeTemplateElements.count(element)) {
                this->timeTemplateElements[element] = timePickerElement()
                    ->setLength(element == TimePickerTemplateElement::Year ? 4 : 2)
                    ->onInput([this, element] (const std::string& newValue) {
                        int newValueInt = std::stoi(newValue);
                        switch (element) {
                            case TimePickerTemplateElement::Year:
                                this->setYear(newValueInt);
                                break;
                            case TimePickerTemplateElement::Month:
                                this->setMonth(newValueInt);
                                break;
                            case TimePickerTemplateElement::Day:
                                this->setDay(newValueInt);
                                break;
                            case TimePickerTemplateElement::Hour:
                                this->setHour(newValueInt);
                                break;
                            case TimePickerTemplateElement::Minute:
                                this->setMinute(newValueInt);
                                break;
                            case TimePickerTemplateElement::Second:
                                this->setSecond(newValueInt);
                                break;
                        }

                        this->updateTime(this->value);
                    })
                    ->onFocus([this, element] () {
                        this->activeTemplateElement = element;
                    })
                    ->onBlur([this, element] () {
                        if (this->activeTemplateElement == element) {
                            this->activeTemplateElement = std::nullopt;
                        }
                    });
            }

            this->timeTemplateRow
                    ->addChild(this->timeTemplateElements[element]);
        }
    }

    void TimePicker::updateTemplate(const std::string &newTemplate) {
        this->timeTemplate.clear();
        for (auto &c : newTemplate) {
            switch (c) {
                case 'Y':
                    this->timeTemplate.push_back(TimePickerTemplateElement::Year);
                    break;
                case 'M':
                    this->timeTemplate.push_back(TimePickerTemplateElement::Month);
                    break;
                case 'D':
                    this->timeTemplate.push_back(TimePickerTemplateElement::Day);
                    break;
                case 'h':
                    this->timeTemplate.push_back(TimePickerTemplateElement::Hour);
                    break;
                case 'm':
                    this->timeTemplate.push_back(TimePickerTemplateElement::Minute);
                    break;
                case 's':
                    this->timeTemplate.push_back(TimePickerTemplateElement::Second);
                    break;
                default:
                    break;
            }
        }
        this->updateTimeTemplateElement();
    }

    void TimePicker::updateTemplate(const std::vector<TimePickerTemplateElement> &newTemplate) {
        this->timeTemplate = newTemplate;
        this->updateTimeTemplateElement();
    }

    std::shared_ptr<TimePicker> TimePicker::setTemplate(const std::string &newTemplate) {
        this->updateTemplate(newTemplate);
        return shared_from_this();
    }

    std::shared_ptr<TimePicker> TimePicker::setTemplate(const std::vector<TimePickerTemplateElement> &newTemplate) {
        return shared_from_this();
    }

    const std::vector<TimePickerTemplateElement> &TimePicker::getTemplate() const {
        return this->timeTemplate;
    }

    void TimePicker::updateTime(const tm &newTime) {
        this->value = newTime;

        this->updateYearElement();
        this->updateMonthElement();
        this->updateDayElement();
        this->updateHourElement();
        this->updateMinuteElement();
        this->updateSecondElement();

        if (this->callbackInput) {
            this->callbackInput();
        }
    }

    std::shared_ptr<TimePicker> TimePicker::setTime(const tm &newTime) {
        this->updateTime(newTime);
        return shared_from_this();
    }

    const tm &TimePicker::getTime() const {
        return this->value;
    }

    std::shared_ptr<TimePicker> TimePicker::setTime(int year, int month, int day, int hour, int minute, int second) {
        this->setYear(year);
        this->setMonth(month);
        this->setDay(day);
        this->setHour(hour);
        this->setMinute(minute);
        this->setSecond(second);
        return shared_from_this();
    }

    std::shared_ptr<TimePicker> TimePicker::setTime(int year, int month, int day, int hour, int minute) {
        this->setYear(year);
        this->setMonth(month);
        this->setDay(day);
        this->setHour(hour);
        this->setMinute(minute);
        return shared_from_this();
    }

    std::shared_ptr<TimePicker> TimePicker::setTime(int year, int month, int day) {
        this->setYear(year);
        this->setMonth(month);
        this->setDay(day);
        return shared_from_this();
    }

    void TimePicker::updateYearElement() {
        if (this->timeTemplateElements.count(TimePickerTemplateElement::Year)) {
            this->timeTemplateElements[TimePickerTemplateElement::Year]->setValue(std::to_string(this->getYear()));
        }
    }

    std::shared_ptr<TimePicker> TimePicker::setYear(int newYear) {
        this->value.tm_year = std::max(newYear - 1900, 0);
        this->updateYearElement();
        return shared_from_this();
    }

    int TimePicker::getYear() const {
        return this->value.tm_year + 1900;
    }

    void TimePicker::updateMonthElement() {
        if (this->timeTemplateElements.count(TimePickerTemplateElement::Month)) {
            this->timeTemplateElements[TimePickerTemplateElement::Month]->setValue(std::to_string(this->getMonth()));
        }
    }

    std::shared_ptr<TimePicker> TimePicker::setMonth(int newMonth) {
        this->value.tm_mon = std::max(std::min(newMonth - 1, 11), 0);
        this->fixValue();
        this->updateMonthElement();
        return shared_from_this();
    }

    int TimePicker::getMonth() const {
        return this->value.tm_mon + 1;
    }

    void TimePicker::updateDayElement() {
        if (this->timeTemplateElements.count(TimePickerTemplateElement::Day)) {
            this->timeTemplateElements[TimePickerTemplateElement::Day]->setValue(std::to_string(this->getDay()));
        }
    }

    std::shared_ptr<TimePicker> TimePicker::setDay(int newDay) {
        this->value.tm_mday = std::max(std::min(newDay, daysInMonth(this->getMonth(), this->getYear())), 0);
        this->fixValue();
        this->updateDayElement();
        return shared_from_this();
    }

    int TimePicker::getDay() const {
        return this->value.tm_mday;
    }

    void TimePicker::updateHourElement() {
        if (this->timeTemplateElements.count(TimePickerTemplateElement::Hour)) {
            this->timeTemplateElements[TimePickerTemplateElement::Hour]->setValue(std::to_string(this->getHour()));
        }
    }

    std::shared_ptr<TimePicker> TimePicker::setHour(int newHour) {
        this->value.tm_hour = std::max(std::min(newHour, 23), 0);
        this->fixValue();
        this->updateHourElement();
        return shared_from_this();
    }

    int TimePicker::getHour() const {
        return this->value.tm_hour;
    }

    void TimePicker::updateMinuteElement() {
        if (this->timeTemplateElements.count(TimePickerTemplateElement::Minute)) {
            this->timeTemplateElements[TimePickerTemplateElement::Minute]->setValue(std::to_string(this->getMinute()));
        }
    }

    std::shared_ptr<TimePicker> TimePicker::setMinute(int newMinute) {
        this->value.tm_min = std::max(std::min(newMinute, 59), 0);
        this->fixValue();
        this->updateMinuteElement();
        return shared_from_this();
    }

    int TimePicker::getMinute() const {
        return this->value.tm_min;
    }

    void TimePicker::updateSecondElement() {
        if (this->timeTemplateElements.count(TimePickerTemplateElement::Second)) {
            this->timeTemplateElements[TimePickerTemplateElement::Second]->setValue(std::to_string(this->getSecond()));
        }
    }

    std::shared_ptr<TimePicker> TimePicker::setSecond(int newSecond) {
        this->value.tm_sec = std::max(std::min(newSecond, 59), 0);
        this->fixValue();
        this->updateSecondElement();
        return shared_from_this();
    }

    int TimePicker::getSecond() const {
        return this->value.tm_sec;
    }

    std::shared_ptr<TimePicker> TimePicker::onInput(const std::function<void()> &callback) {
        this->callbackInput = callback;
        return shared_from_this();
    }

    EventCallbackResponse TimePicker::onEvent(std::shared_ptr<EventKeyboard> event) {
        if (this->activeTemplateElement && (event->action == KeyAction::Press || event->action == KeyAction::Repeat)) {
            if (event->key == KeyboardKey::Tab && event->mod != KeyMod::Shift || event->key == KeyboardKey::Right) {
                auto element = this->activeTemplateElement.value();

                // TODO: Refactor with Focusable and FocusableTrap
                auto elementIndex = std::find(this->timeTemplate.begin(), this->timeTemplate.end(), element);
                std::vector<TimePickerTemplateElement>::iterator nextElementIndex;
                if (elementIndex == this->timeTemplate.end() - 1) {
                    nextElementIndex = this->timeTemplate.begin();
                } else {
                    nextElementIndex = elementIndex + 1;
                }
                auto nextElement = *nextElementIndex;

                this->timeTemplateElements[element]->blur();

                this->activeTemplateElement = nextElement;
                this->timeTemplateElements[nextElement]->focus();
            } else if (event->key == KeyboardKey::Tab && event->mod == KeyMod::Shift || event->key == KeyboardKey::Left) {
                auto element = this->activeTemplateElement.value();

                // TODO: Refactor with Focusable and FocusableTrap
                auto elementIndex = std::find(this->timeTemplate.begin(), this->timeTemplate.end(), element);
                std::vector<TimePickerTemplateElement>::iterator nextElementIndex;
                if (elementIndex == this->timeTemplate.begin()) {
                    nextElementIndex = this->timeTemplate.end() - 1;
                } else {
                    nextElementIndex = elementIndex - 1;
                }
                auto nextElement = *nextElementIndex;

                this->timeTemplateElements[element]->blur();

                this->activeTemplateElement = nextElement;
                this->timeTemplateElements[nextElement]->focus();
            }
        }
    }

    void TimePicker::fixValue() {
        this->value.tm_isdst = -1;
        mktime(&this->value);
    }

    TimePickerElement::TimePickerElement() {
        this->backgroundElement = background();
        this->textElement = text();
        this->inputableElement = inputable();
        this->element = rounded()
            ->setRadius(2)
            ->setChild(hoverable()
                ->setChild(withCursor()
                    ->setChild(this->inputableElement
                        ->setChild(this->backgroundElement
                            ->setColor("#F5F5F5")
                            ->setChild(padding()
                                ->setPaddings(2,4,6,4)
                                ->setChild(height()
                                    ->setHeight(15)
                                    ->setChild(this->textElement
                                        ->setFontColor("#3F4944")
                                        ->setFontSize(16)
                                        ->setFontWeight(500)
                                        ->setFontFamily("Fira Code")))))
                        ->onChange([this] (std::u32string newValue) {
                            std::string newValueDigitsOnly;
                            for (auto c : newValue) {
                                if (c >= '0' && c <= '9') {
                                    newValueDigitsOnly += c;
                                }
                            }

                            std::string newValueFitted = leftPadAndFit(newValueDigitsOnly, this->length, '0');
                            this->textElement->setText(newValueFitted);

                            std::u32string newValueFittedU32;
                            fromUTF8(newValueFitted, newValueFittedU32);
                            return newValueFittedU32;
                        })
                        ->onFocus([this] () {
                            this->focused = true;
                            this->backgroundElement->setColor("#E2E2E2");

                            if (this->callbackFocus) {
                                this->callbackFocus();
                            }
                        })
                        ->onBlur([this] () {
                            this->focused = false;
                            this->backgroundElement->setColor("#F5F5F5");

                            auto newValue = this->textElement->getText();
                            if (this->value != newValue && this->callbackInput) {
                                this->callbackInput(newValue);
                                this->value = newValue;
                            }

                            if (this->callbackBlur) {
                                this->callbackBlur();
                            }
                        }))
                    ->setCursorShape(CursorShape::IBeam))
                ->onEnter([this]() { this->backgroundElement->setColor("#E2E2E2"); })
                ->onLeave([this]() {
                    if (!this->focused) {
                        this->backgroundElement->setColor("#F5F5F5");
                    }
                }));
    }

    std::shared_ptr<TimePickerElement> timePickerElement() {
        return std::make_shared<TimePickerElement>();
    }

    std::shared_ptr<TimePickerElement> TimePickerElement::setLength(unsigned int newLength) {
        this->length = newLength;
        return shared_from_this();
    }

    unsigned int TimePickerElement::getLength() const {
        return this->length;
    }

    std::shared_ptr<TimePickerElement> TimePickerElement::setValue(const std::string& newValue) {
        this->value = leftPadAndFit(newValue, this->length, '0');
        this->inputableElement->setText(this->value);
        this->textElement->setText(this->value);
        return shared_from_this();
    }

    std::string TimePickerElement::getValue() const {
        return this->value;
    }

    std::shared_ptr<TimePickerElement> TimePickerElement::onInput(const std::function<void(std::string text)> &callback) {
        this->callbackInput = callback;
        return shared_from_this();
    }

    void TimePickerElement::blur() {
        this->inputableElement->blur();
    }

    void TimePickerElement::focus() {
        this->inputableElement->focus();
    }

    std::shared_ptr<TimePickerElement> TimePickerElement::onFocus(const std::function<void()> &callback) {
        this->callbackFocus = callback;
        return shared_from_this();
    }

    std::shared_ptr<TimePickerElement> TimePickerElement::onBlur(const std::function<void()> &callback) {
        this->callbackBlur = callback;
        return shared_from_this();
    }

    EventCallbackResponse TimePickerElement::onEvent(std::shared_ptr<EventKeyboard> event) {
        if (this->focused && (event->action == KeyAction::Press || event->action == KeyAction::Repeat)) {
            if (event->key == KeyboardKey::Up) {
                int value = std::stoi(this->textElement->getText());
                this->inputableElement->setText(std::to_string(value + 1));
                return EventCallbackResponse::StopPropagation;
            }

            if (event->key == KeyboardKey::Down) {
                int value = std::stoi(this->textElement->getText());
                this->inputableElement->setText(std::to_string(std::max(value - 1, 0)));
                return EventCallbackResponse::StopPropagation;
            }
        }

        return EventCallbackResponse::None;
    }
}