//
// Created by noartem on 28.05.2022.
//

#include "../library/Element.h"
#include "../library/Column.h"
#include "../library/Scrollable.h"
#include "../library/Scrollbar.h"
#include "../library/Background.h"
#include "../library/Rounded.h"
#include "../library/Padding.h"
#include "../library/Hoverable.h"
#include "../library/Clickable.h"
#include "../library/Flex.h"
#include "../library/Flexible.h"
#include "../library/Sized.h"
#include "../library/Align.h"
#include "../library/Label.h"
#include "../library/Application.h"
#include "../library/Platform.h"

using namespace elementor;

#include <vector>

class Example {
public:
    virtual std::string getName() = 0;

    virtual std::string getDescription() = 0;

    virtual Element *getScene() = 0;
};

class ExampleFlexAlignment: public Example {
    std::string getName() {
        return "Flex alignment";
    }

    std::string getDescription() {
        return "Flex children can be aligned by two axis";
    }

    Element *makeRow(FlexAlignment alignment, FlexCrossAlignment crossAlignment) {
        return flexible()
            ->setChild(flex()
                ->setSpacing(16)
                ->setAlignment(alignment)
                ->setCrossAlignment(crossAlignment)
                ->appendChild(sized()
                    ->setSize(280, 200)
                    ->setChild(background()
                        ->setColor("#457b9d")))
                ->appendChild(sized()
                    ->setSize(200, 80)
                    ->setChild(background()
                        ->setColor("#a8dadc"))));
    }

    Element *getScene() {
        return flex()
            ->setSpacing(24)
            ->setDirection(FlexDirection::Column)
            ->appendChild(this->makeRow(FlexAlignment::Start, FlexCrossAlignment::SpaceEvenly))
            ->appendChild(this->makeRow(FlexAlignment::Center, FlexCrossAlignment::SpaceEvenly))
            ->appendChild(this->makeRow(FlexAlignment::End, FlexCrossAlignment::SpaceEvenly));
    }
};

class ExampleFlexChildren: public Example {
    std::string getName() {
        return "Flex children";
    }

    std::string getDescription() {
        return "Flex children can be Flexible, Expanded or Sized (by default)";
    }

    Element *getScene() {
        return flex()
            ->setSpacing(24)
            ->setDirection(FlexDirection::Column)
            ->appendChild(flexible()
                ->setChild(flex()
                    ->setSpacing(16)
                    ->appendChild(flexible()
                        ->setChild(background()
                            ->setColor("#457B9D")))
                    ->appendChild(flexible()
                        ->setChild(background()
                            ->setColor("#457B9D")))))
            ->appendChild(flexible()
                ->setChild(flex()
                    ->setSpacing(16)
                    ->appendChild(sized()
                        ->setSize(120)
                        ->setChild(background()
                            ->setColor("#457B9D")))
                    ->appendChild(sized()
                        ->setSize(120)
                        ->setChild(background()
                            ->setColor("#457B9D")))))
            ->appendChild(flexible()
                ->setChild(flex()
                    ->setSpacing(16)
                    ->appendChild(flexible()
                        ->setChild(align()
                            ->setAlignment(Alignment::TopLeft)
                            ->setChild(sized()
                                ->setSize(120)
                                ->setChild(background()
                                    ->setColor("#457B9D")))))
                    ->appendChild(flexible()
                        ->setChild(align()
                            ->setAlignment(Alignment::TopLeft)
                            ->setChild(sized()
                                ->setSize(120)
                                ->setChild(background()
                                    ->setColor("#457B9D")))))));
    }
};

int main() {
    std::vector <Example *> examples;
    examples.push_back((Example *) new ExampleFlexChildren());
    examples.push_back((Example *) new ExampleFlexAlignment());

    Background *activeExampleElement = background();

    Column *examplesList = column();
    for (Example *example : examples) {
        Background *buttonBackground = background();
        examplesList
            ->appendChild(clickable()
                ->setChild(hoverable()
                    ->setChild(rounded()
                        ->setRadius(24)
                        ->setChild(buttonBackground
                            ->setColor("#F7F4E8")
                            ->setChild(padding()
                                ->setPaddings(12, 18)
                                ->setChild(label()
                                    ->setFontColor("#1C1D07")
                                    ->setFontSize(16)
                                    ->setText(example->getName())))))
                    ->onEnter([buttonBackground] () { buttonBackground->setColor("#E6E4C2"); })
                    ->onLeave([buttonBackground] () { buttonBackground->setColor("#F7F4E8"); }))
                ->onClick([example, activeExampleElement] () { activeExampleElement->setChild(example->getScene()); }));
    }

    Application *application = new Application();
    application->root = background()
        ->setColor("#FFFCF3")
        ->setChild(flex()
            ->setSpacing(12)
            ->appendChild(flexible()
                ->setGrow(1)
                ->setChild(background()
                    ->setColor("#F7F4E8")
                    ->setChild(padding()
                        ->setPaddings(18)
                        ->setChild(scrollbar()
                            ->setChild(scrollable()
                                ->setDirection(ScrollDirection::Vertical)
                                ->setChild(examplesList))))))
            ->appendChild(flexible()
                ->setGrow(3)
                ->setChild(padding()
                    ->setPaddings(18)
                    ->setChild(rounded()
                        ->setChild(activeExampleElement)))));

    Platform *platform = new Platform();
    platform->title = "Elementor examples";
    platform->size = {920, 640};
    platform->minSize = {640, 320};
    platform->application = application;

    platform->run();
}