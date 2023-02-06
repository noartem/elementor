//
// Created by noartem on 05.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_COMBOX_H
#define ELEMENTOR_COMPONENTS_COMBOX_H

#include "utility.h"
#include "elementor.h"
#include "Tooltip.h"

namespace elementor::components {
    class Combox : public Component {
    public:
        Combox();

        Combox *setOptions(std::vector<std::tuple<std::string, std::string>> newOptions);

        Combox *addOption(std::tuple<std::string, std::string> option);

        Combox *addOption(const std::string &value, const std::string &label);

        void removeOption(size_t i);

        void removeOption(const std::string &optionValue);

        void removeOption(const std::tuple<std::string, std::string> &option);

        [[nodiscard]] std::vector<std::tuple<std::string, std::string>> getOptions() const;

        [[nodiscard]] size_t getOptionsSize() const;

        [[nodiscard]] std::tuple<std::string, std::string> getOption(size_t i) const;

        [[nodiscard]] size_t optionIndex(const std::tuple<std::string, std::string> &option) const;

        [[nodiscard]] size_t optionIndex(const std::string &optionValue) const;

        Combox *setValue(std::tuple<std::string, std::string> option);

        Combox *setValue(const std::string &optionValue);

        [[nodiscard]] std::string getValue() const;

        Combox *onChange(std::function<void(std::string value)> callback);

        Combox *setPlaceholder(const std::string& newPlaceholder);

        [[nodiscard]] std::string getPlaceholder() const;

    private:
        std::shared_ptr<Paragraph> paragraphElement;
        std::shared_ptr<Text> textElement;
        std::shared_ptr<Border> borderElement;
        Tooltip *tooltipElement;
        std::shared_ptr<Column> optionsColumnElement = nullptr;
        std::shared_ptr<Width> tipWidthElement = nullptr;
        std::vector<std::tuple<std::string, std::string>> options;
        std::string value;
        std::function<void(std::string text)> callbackChange;
        std::string placeholder;

        void updateOptionsElement();
    };

    Combox *combox();
}

#endif //ELEMENTOR_COMPONENTS_COMBOX_H
