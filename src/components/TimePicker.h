//
// Created by noartem on 10.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_TIME_PICKER_H
#define ELEMENTOR_COMPONENTS_TIME_PICKER_H

#include "utility.h"
#include "elementor.h"
#include "Tooltip.h"

namespace elementor::components {
    enum class TimePickerTemplateElement {
        Year,
        Month,
        Day,
        Hour,
        Minute,
        Second,
    };

    class TimePickerElement : public Component, public std::enable_shared_from_this<TimePickerElement> {
    public:
        TimePickerElement();

        std::shared_ptr<TimePickerElement> setLength(unsigned int newLength);

        [[nodiscard]] unsigned int getLength() const;

        std::shared_ptr<TimePickerElement> setValue(const std::string &newValue);

        [[nodiscard]] std::string getValue() const;

        std::shared_ptr<TimePickerElement> onInput(const std::function<void(std::string text)> &callback);

    private:
        unsigned int length = 0;
        std::string value;
        bool focused = false;
        std::function<void(std::string text)> callbackInput;
        std::shared_ptr<Background> backgroundElement;
        std::shared_ptr<Text> textElement;
        std::shared_ptr<Inputable> inputableElement;
    };

    std::shared_ptr<TimePickerElement> timePickerElement();

    class TimePicker : public Component, public std::enable_shared_from_this<TimePicker> {
    public:
        TimePicker();

        std::shared_ptr<TimePicker> setTemplate(const std::string &newTemplate);

        std::shared_ptr<TimePicker> setTemplate(const std::vector<TimePickerTemplateElement> &newTemplate);

        [[nodiscard]] const std::vector<TimePickerTemplateElement> &getTemplate() const;

        std::shared_ptr<TimePicker> setTime(const tm &newTime);

        [[nodiscard]] const tm &getTime() const;

        std::shared_ptr<TimePicker> setTime(int year, int month, int day, int hour, int minute, int second);

        std::shared_ptr<TimePicker> setTime(int year, int month, int day, int hour, int minute);

        std::shared_ptr<TimePicker> setTime(int year, int month, int day);

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

        std::shared_ptr<TimePicker> onInput(const std::function<void()> &callback);

    private:
        tm value;
        std::vector<TimePickerTemplateElement> timeTemplate = {};
        std::function<void()> callbackInput;

        std::shared_ptr<Row> timeTemplateRow;
        std::map<TimePickerTemplateElement, std::shared_ptr<TimePickerElement>> timeTemplateElements;

        void updateTimeTemplateElement();

        void updateTemplate(const std::vector<TimePickerTemplateElement> &newTemplate);
        void updateTemplate(const std::string &newTemplate);

        void updateYearElement();
        void updateMonthElement();
        void updateDayElement();
        void updateHourElement();
        void updateMinuteElement();
        void updateSecondElement();

        void updateTime(const tm &newTime);
    };

    std::shared_ptr<TimePicker> timePicker();
}

#endif //ELEMENTOR_COMPONENTS_TIME_PICKER_H
