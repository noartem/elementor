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
                                    ->setChild(this->timeTemplateRow))))));

        this->updateTime(now_tm());
        this->updateTemplate("D.M.Y h:m");
    }

    void TimePicker::setTimePartValue(PartType element, int newValue) {
        switch (element) {
            case PartType::Year:
                this->setYear(newValue);
                break;
            case PartType::Month:
                this->setMonth(newValue);
                break;
            case PartType::Day:
                this->setDay(newValue);
                break;
            case PartType::Hour:
                this->setHour(newValue);
                break;
            case PartType::Minute:
                this->setMinute(newValue);
                break;
            case PartType::Second:
                this->setSecond(newValue);
                break;
        }
    }

    std::shared_ptr<TimePicker::Part> TimePicker::makePart(PartType partType) {
        auto part = std::make_shared<Part>(partType);
        part->length = partType == PartType::Year ? 4 : 2;
        part->callbackInput = [this, partType] (const std::string& newValue) {
            this->setTimePartValue(partType, std::stoi(newValue));
            this->updateTime(this->value);
        };
        part->callbackFocus = [this, partType] () {
            if (this->activePart != partType) {
                this->setActivePart(partType);
            }
        };
        part->callbackBlur = [this, partType] () {
            if (this->activePart == partType) {
                this->setActivePart(std::nullopt);
            }
        };

        return part;
    }

    std::shared_ptr<Element> TimePicker::makeGapElement(const std::string &gap) {
        return padding()
            ->setPaddings(0, 6, 5, 0)
            ->setChild(text()
                ->setFontColor("#3F4944")
                ->setFontSize(16)
                ->setFontWeight(500)
                ->setFontFamily("Fira Code")
                ->setText(gap));
    }

    void TimePicker::updateTimeTemplateElement() {
        this->timeTemplateRow->clearChildren();

        for (size_t i = 0; i < this->timeTemplate.size(); i++) {
            auto gap = this->timeTemplateGaps[i];
            if (!gap.empty()) {
                this->timeTemplateRow
                    ->appendChild(this->makeGapElement(gap));
            }

            auto partType = this->timeTemplate[i];
            if (!this->timeTemplateParts.count(partType)) {
                this->timeTemplateParts[partType] = this->makePart(partType);
            }

            this->timeTemplateRow
                ->addChild(this->timeTemplateParts[partType]);
        }

        auto gap = this->timeTemplateGaps[this->timeTemplateGaps.size() - 1];
        if (!gap.empty()) {
            this->timeTemplateRow
                ->appendChild(this->makeGapElement(gap));
        }
    }

    void TimePicker::updateTemplate(const std::string &newTemplate) {
        this->timeTemplate.clear();
        this->timeTemplateGaps.clear();
        std::string gap;
        for (auto &c : newTemplate) {
            switch (c) {
                case 'Y':
                    this->timeTemplateGaps.push_back(gap);
                    gap.clear();
                    this->timeTemplate.push_back(PartType::Year);
                    break;
                case 'M':
                    this->timeTemplateGaps.push_back(gap);
                    gap.clear();
                    this->timeTemplate.push_back(PartType::Month);
                    break;
                case 'D':
                    this->timeTemplateGaps.push_back(gap);
                    gap.clear();
                    this->timeTemplate.push_back(PartType::Day);
                    break;
                case 'h':
                    this->timeTemplateGaps.push_back(gap);
                    gap.clear();
                    this->timeTemplate.push_back(PartType::Hour);
                    break;
                case 'm':
                    this->timeTemplateGaps.push_back(gap);
                    gap.clear();
                    this->timeTemplate.push_back(PartType::Minute);
                    break;
                case 's':
                    this->timeTemplateGaps.push_back(gap);
                    gap.clear();
                    this->timeTemplate.push_back(PartType::Second);
                    break;
                default:
                    gap += c;
                    break;
            }
        }
        this->timeTemplateGaps.push_back(gap);
        this->updateTimeTemplateElement();
    }

    std::shared_ptr<TimePicker> TimePicker::setTemplate(const std::string &newTemplate) {
        this->updateTemplate(newTemplate);
        return shared_from_this();
    }

    void TimePicker::fixValue() {
        this->value.tm_isdst = -1;
        mktime(&this->value);
    }

    void TimePicker::updateYearElement() {
        if (this->timeTemplateParts.count(PartType::Year)) {
            this->timeTemplateParts[PartType::Year]->setValue(std::to_string(this->getYear()));
        }
    }

    void TimePicker::updateYear(int newYear) {
        this->value.tm_year = std::max(newYear - 1900, 0);
    }

    std::shared_ptr<TimePicker> TimePicker::setYear(int newYear) {
        this->updateYear(newYear);
        this->fixValue();

        this->updateYearElement();

        if (this->callbackInput) {
            this->callbackInput();
        }

        return shared_from_this();
    }

    int TimePicker::getYear() const {
        return this->value.tm_year + 1900;
    }

    void TimePicker::updateMonthElement() {
        if (this->timeTemplateParts.count(PartType::Month)) {
            this->timeTemplateParts[PartType::Month]->setValue(std::to_string(this->getMonth()));
        }
    }

    void TimePicker::updateMonth(int newMonth) {
        this->value.tm_mon = std::min(std::max(newMonth, 1), 12) - 1;
    }

    std::shared_ptr<TimePicker> TimePicker::setMonth(int newMonth) {
        this->updateMonth(newMonth);
        this->fixValue();

        this->updateMonthElement();

        if (this->callbackInput) {
            this->callbackInput();
        }

        return shared_from_this();
    }

    int TimePicker::getMonth() const {
        return this->value.tm_mon + 1;
    }

    void TimePicker::updateDayElement() {
        if (this->timeTemplateParts.count(PartType::Day)) {
            this->timeTemplateParts[PartType::Day]->setValue(std::to_string(this->getDay()));
        }
    }

    void TimePicker::updateDay(int newDay) {
        this->value.tm_mday = std::max(std::min(newDay, daysInMonth(this->getMonth(), this->getYear())), 0);
    }

    std::shared_ptr<TimePicker> TimePicker::setDay(int newDay) {
        this->updateDay(newDay);
        this->fixValue();

        this->updateDayElement();

        if (this->callbackInput) {
            this->callbackInput();
        }

        return shared_from_this();
    }

    int TimePicker::getDay() const {
        return this->value.tm_mday;
    }

    void TimePicker::updateHourElement() {
        if (this->timeTemplateParts.count(PartType::Hour)) {
            this->timeTemplateParts[PartType::Hour]->setValue(std::to_string(this->getHour()));
        }
    }

    void TimePicker::updateHour(int newHour) {
        this->value.tm_hour = std::max(std::min(newHour, 23), 0);
    }

    std::shared_ptr<TimePicker> TimePicker::setHour(int newHour) {
        this->updateHour(newHour);
        this->fixValue();

        this->updateHourElement();

        if (this->callbackInput) {
            this->callbackInput();
        }

        return shared_from_this();
    }

    int TimePicker::getHour() const {
        return this->value.tm_hour;
    }

    void TimePicker::updateMinuteElement() {
        if (this->timeTemplateParts.count(PartType::Minute)) {
            this->timeTemplateParts[PartType::Minute]->setValue(std::to_string(this->getMinute()));
        }
    }

    void TimePicker::updateMinute(int newMinute) {
        this->value.tm_min = std::max(std::min(newMinute, 59), 0);
    }

    std::shared_ptr<TimePicker> TimePicker::setMinute(int newMinute) {
        this->updateMinute(newMinute);
        this->fixValue();

        this->updateMinuteElement();

        if (this->callbackInput) {
            this->callbackInput();
        }

        return shared_from_this();
    }

    int TimePicker::getMinute() const {
        return this->value.tm_min;
    }

    void TimePicker::updateSecondElement() {
        if (this->timeTemplateParts.count(PartType::Second)) {
            this->timeTemplateParts[PartType::Second]->setValue(std::to_string(this->getSecond()));
        }
    }

    void TimePicker::updateSecond(int newSecond) {
        this->value.tm_sec = std::max(std::min(newSecond, 59), 0);
    }

    std::shared_ptr<TimePicker> TimePicker::setSecond(int newSecond) {
        this->updateSecond(newSecond);
        this->fixValue();

        this->updateSecondElement();

        if (this->callbackInput) {
            this->callbackInput();
        }

        return shared_from_this();
    }

    int TimePicker::getSecond() const {
        return this->value.tm_sec;
    }

    void TimePicker::updateTimeElements() {
        this->updateYearElement();
        this->updateMonthElement();
        this->updateDayElement();
        this->updateHourElement();
        this->updateMinuteElement();
        this->updateSecondElement();
    }

    void TimePicker::updateTime(const tm &newTime) {
        this->value = newTime;
    }

    std::shared_ptr<TimePicker> TimePicker::setTime(const tm &newTime) {
        this->updateTime(newTime);

        this->updateTimeElements();

        if (this->callbackInput) {
            this->callbackInput();
        }

        return shared_from_this();
    }

    std::shared_ptr<TimePicker> TimePicker::setTime(int year, int month, int day, int hour, int minute, int second) {
        this->updateYear(year);
        this->updateMonth(month);
        this->updateDay(day);
        this->updateHour(hour);
        this->updateMinute(minute);
        this->updateSecond(second);

        this->updateTimeElements();

        if (this->callbackInput) {
            this->callbackInput();
        }

        return shared_from_this();
    }

    std::shared_ptr<TimePicker> TimePicker::setTime(int year, int month, int day, int hour, int minute) {
        this->updateYear(year);
        this->updateMonth(month);
        this->updateDay(day);
        this->updateHour(hour);
        this->updateMinute(minute);

        this->updateTimeElements();

        if (this->callbackInput) {
            this->callbackInput();
        }

        return shared_from_this();
    }

    std::shared_ptr<TimePicker> TimePicker::setTime(int year, int month, int day) {
        this->updateYear(year);
        this->updateMonth(month);
        this->updateDay(day);

        this->updateTimeElements();

        if (this->callbackInput) {
            this->callbackInput();
        }

        return shared_from_this();
    }

    const tm &TimePicker::getTime() const {
        return this->value;
    }

    std::shared_ptr<TimePicker> TimePicker::onInput(const std::function<void()> &callback) {
        this->callbackInput = callback;
        return shared_from_this();
    }

    std::shared_ptr<TimePicker> TimePicker::onFocus(const std::function<void()> &callback) {
        this->callbackFocus = callback;
        return shared_from_this();
    }

    std::shared_ptr<TimePicker> TimePicker::onBlur(const std::function<void()> &callback) {
        this->callbackBlur = callback;
        return shared_from_this();
    }

    void TimePicker::setActivePart(std::optional<PartType> partType) {
        if (this->activePart) {
            this->timeTemplateParts[this->activePart.value()]->blur();

            if (!partType && this->callbackBlur) {
                this->callbackBlur();
            }
        }

        if (!this->activePart && this->callbackFocus) {
            this->callbackFocus();
        }

        if (partType) {
            this->activePart = partType.value();
            this->timeTemplateParts[partType.value()]->focus();
        }
    }

    EventCallbackResponse TimePicker::onEvent(std::shared_ptr<KeyboardEvent> event) {
        if (this->activePart && (event->action == KeyAction::Press || event->action == KeyAction::Repeat)) {
            if ((event->key == KeyboardKey::Tab && event->mod != KeyMod::Shift) || event->key == KeyboardKey::Right) {
                PartType partType = this->activePart.value();

                auto partIndex = std::find(this->timeTemplate.begin(), this->timeTemplate.end(), partType);
                std::vector<PartType>::iterator nextPartIndex;
                if (partIndex == this->timeTemplate.end() - 1) {
                    nextPartIndex = this->timeTemplate.begin();
                } else {
                    nextPartIndex = partIndex + 1;
                }
                auto nextPart = *nextPartIndex;

                this->timeTemplateParts[partType]->blur();

                this->setActivePart(nextPart);
                this->timeTemplateParts[nextPart]->focus();

                return EventCallbackResponse::StopPropagation;
            }

            if ((event->key == KeyboardKey::Tab && event->mod == KeyMod::Shift) || (event->key == KeyboardKey::Left)) {
                auto partType = this->activePart.value();

                auto partIndex = std::find(this->timeTemplate.begin(), this->timeTemplate.end(), partType);
                std::vector<PartType>::iterator nextPartIndex;
                if (partIndex == this->timeTemplate.begin()) {
                    nextPartIndex = this->timeTemplate.end() - 1;
                } else {
                    nextPartIndex = partIndex - 1;
                }
                auto nextPart = *nextPartIndex;

                this->timeTemplateParts[partType]->blur();

                this->setActivePart(nextPart);
                this->timeTemplateParts[nextPart]->focus();
                return EventCallbackResponse::StopPropagation;
            }
        }

        return EventCallbackResponse::None;
    }

    TimePicker::Part::Part(PartType partType) {
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
                        ->onChange([this] (const std::u32string &newValue) {
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
                ->onEnter([this]() {
                    if (!this->focused) {
                        this->backgroundElement->setColor("#E2E2E2");
                    }
                })
                ->onLeave([this]() {
                    if (!this->focused) {
                        this->backgroundElement->setColor("#F5F5F5");
                    }
                }));
    }

    void TimePicker::Part::blur() {
        if (this->inputableElement) {
            this->inputableElement->blur();
        }
    }

    void TimePicker::Part::focus() {
        if (this->inputableElement) {
            this->inputableElement->focus();
        }
    }

    void TimePicker::Part::setValue(const std::string& newValue) {
        this->value = leftPadAndFit(newValue, this->length, '0');
        this->inputableElement->setText(this->value);
        this->textElement->setText(this->value);
    }

    EventCallbackResponse TimePicker::Part::onEvent(std::shared_ptr<KeyboardEvent> event) {
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