//
// Created by noartem on 05.02.2023.
//

#ifndef ELEMENTOR_COMPONENTS_COMBOX_H
#define ELEMENTOR_COMPONENTS_COMBOX_H

#include "utility.h"
#include "elementor.h"
#include "Tooltip.h"

namespace elementor::components {
    class Combox : public Component, public std::enable_shared_from_this<Combox> {
    public:
        Combox();

        std::shared_ptr<Combox> setOptions(std::vector<std::tuple<std::string, std::string>> newOptions);

        std::shared_ptr<Combox> addOption(const std::tuple<std::string, std::string>& option);

        std::shared_ptr<Combox> addOption(const std::string &value, const std::string &label);

        void removeOption(size_t i);

        void removeOption(const std::string &optionValue);

        void removeOption(const std::tuple<std::string, std::string> &option);

        [[nodiscard]] std::vector<std::tuple<std::string, std::string>> getOptions() const;

        [[nodiscard]] size_t getOptionsSize() const;

        [[nodiscard]] std::tuple<std::string, std::string> getOption(size_t i) const;

        [[nodiscard]] size_t optionIndex(const std::tuple<std::string, std::string> &option) const;

        [[nodiscard]] size_t optionIndex(const std::string &optionValue) const;

        std::shared_ptr<Combox> setValue(std::tuple<std::string, std::string> option);

        std::shared_ptr<Combox> setValue(const std::string &optionValue);

        [[nodiscard]] std::string getValue() const;

        std::shared_ptr<Combox> onChange(std::function<void(std::string value)> callback);

        std::shared_ptr<Combox> setPlaceholder(const std::string& newPlaceholder);

        [[nodiscard]] std::string getPlaceholder() const;

        void setActive(bool active);

        void toggleActive();

        bool getActive() const;

    private:
        std::shared_ptr<Paragraph> paragraphElement;
        std::shared_ptr<Text> textElement;
        std::shared_ptr<Border> borderElement;
        std::shared_ptr<Tooltip> tooltipElement;
        std::vector<std::tuple<std::string, std::string>> options;
        std::string value;
        std::string placeholder;
        std::function<void(std::string text)> callbackChange;

        std::shared_ptr<Element> renderTip();

        std::shared_ptr<Element> renderOptions();
    };

    std::shared_ptr<Combox> combox();
}

#endif //ELEMENTOR_COMPONENTS_COMBOX_H
