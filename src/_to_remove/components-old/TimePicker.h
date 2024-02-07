//
// Created by noartem on 10.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_TIME_PICKER_H
#define ELEMENTOR_COMPONENTS_TIME_PICKER_H

#include "utility.h"
#include "elementor.h"
#include "Tooltip.h"

namespace elementor::components {
    class TimePicker : public Component, public WithOnKeyboard, public std::enable_shared_from_this<TimePicker> {
    public:
        TimePicker();

        std::shared_ptr<TimePicker> setTemplate(const std::string &newTemplate);

        std::shared_ptr<TimePicker> setYear(int newYear);

        [[nodiscard]] int getYear() const;

        std::shared_ptr<TimePicker> setMonth(int newMonth);

        [[nodiscard]] int getMonth() const;

        std::shared_ptr<TimePicker> setDay(int newDay);

        [[nodiscard]] int getDay() const;

        std::shared_ptr<TimePicker> setHour(int newHour);

        [[nodiscard]] int getHour() const;

        std::shared_ptr<TimePicker> setMinute(int newMinute);

        [[nodiscard]] int getMinute() const;

        std::shared_ptr<TimePicker> setSecond(int newSecond);

        [[nodiscard]] int getSecond() const;

        std::shared_ptr<TimePicker> setTime(const tm &newTime);

        std::shared_ptr<TimePicker> setTime(int year, int month, int day, int hour, int minute, int second);

        std::shared_ptr<TimePicker> setTime(int year, int month, int day, int hour, int minute);

        std::shared_ptr<TimePicker> setTime(int year, int month, int day);

        [[nodiscard]] const tm &getTime() const;

        std::shared_ptr<TimePicker> onInput(const std::function<void()> &callback);

        std::shared_ptr<TimePicker> onFocus(const std::function<void()> &callback);

        std::shared_ptr<TimePicker> onBlur(const std::function<void()> &callback);

        EventCallbackResponse onEvent(std::shared_ptr<KeyboardEvent> event) override;

    private:
        enum class PartType {
            Year,
            Month,
            Day,
            Hour,
            Minute,
            Second,
        };

        class Part : public Component, public WithOnKeyboard, public std::enable_shared_from_this<Part> {
        public:
            Part(PartType partType);

            PartType partType;
            unsigned int length = 0;
            std::string value;
            bool focused = false;
            std::function<void(std::string text)> callbackInput;
            std::function<void()> callbackFocus;
            std::function<void()> callbackBlur;
            std::shared_ptr<Background> backgroundElement;
            std::shared_ptr<Text> textElement;
            std::shared_ptr<Inputable> inputableElement;

            void blur();

            void focus();

            void setValue(const std::string &newValue);

            EventCallbackResponse onEvent(std::shared_ptr<KeyboardEvent> event) override;
        };

        tm value{};
        std::optional<PartType> activePart = std::nullopt;
        std::vector<PartType> timeTemplate = {};
        std::vector<std::string> timeTemplateGaps = {};
        std::function<void()> callbackInput;
        std::function<void()> callbackFocus;
        std::function<void()> callbackBlur;

        std::shared_ptr<Row> timeTemplateRow;
        std::map<PartType, std::shared_ptr<Part>> timeTemplateParts;

        std::shared_ptr<Part> makePart(PartType partType);
        std::shared_ptr<Element> makeGapElement(const std::string &gap);
        void updateTimeTemplateElement();

        void updateTemplate(const std::string &newTemplate);

        void updateYear(int newYear);
        void updateMonth(int newMonth);
        void updateDay(int newDay);
        void updateHour(int newHour);
        void updateMinute(int newMinute);
        void updateSecond(int newSecond);

        void updateYearElement();
        void updateMonthElement();
        void updateDayElement();
        void updateHourElement();
        void updateMinuteElement();
        void updateSecondElement();

        void updateTimeElements();

        void updateTime(const tm &newTime);

        void setTimePartValue(PartType element, int newValue);

        void fixValue();

        void setActivePart(std::optional<PartType> partType);
    };

    std::shared_ptr<TimePicker> timePicker();
}

#endif //ELEMENTOR_COMPONENTS_TIME_PICKER_H
