//
// Created by noartem on 03.06.2022.
//

#include "ExamplesGallery.h"
#include "Examples.h"

ExamplesGallery::ExamplesGallery() {
    this->activeExampleElement = empty();
    this->activeExampleLabelName = empty();
    this->activeExampleLabelDescription = empty();

    this->element = background()
        ->setColor("#FFFFFF")
        ->setChild(flex()
            ->appendChild(width()
                ->setWidth(200)
                    ->setChild(background()
                        ->setColor("#EDF5F0")
                        ->setChild(padding()
                            ->setPaddings(12, 18)
                            ->setChild(flex()
                                ->setSpacing(6)
                                ->setDirection(FlexDirection::Column)
                                ->appendChild(clickable()
                                    ->setChild(text()
                                        ->setFontColor("#191C1A")
                                        ->setFontSize(18)
                                        ->setFontWeight(500)
                                        ->setFontFamily("Fira Code")
                                        ->setText("Examples"))
                                    ->onClick([this] () {
                                        this->ctx->requestNextFrame([this] () {
                                            auto window = this->ctx->makeWindow({920, 640});
                                            window->setTitle("Elementor Examples");
                                            auto rootElement = std::make_shared<ExamplesGallery>();
                                            auto componentsContext = std::make_shared<ComponentsContext>(rootElement);
                                            window->setUserPointer(componentsContext);
                                            window->setRoot(componentsContext);
                                            window->setMinSize({630, 320});
                                        });
                                    }))
                                ->appendChild(empty())
                                ->appendChild(flexible()
                                    ->setChild(rounded()
                                        ->setRadius(8)
                                        ->setChild(scrollable()
                                            ->setDirection(ScrollDirection::Vertical)
                                            ->setChild(rounded()
                                                ->setRadius(8)
                                                ->setChild(background()
                                                    ->setColor("#DEEDE6")
                                                    ->setChild(expandedWidth()
                                                        ->setChild(this->makeExamplesList())))))))
                                ->appendChild(scaleControl())
                                ->appendChild(fpsLabel())))))
            ->appendChild(flexible()
                ->setGrow(3)
                ->setChild(flex()
                    ->setDirection(FlexDirection::Column)
                    ->appendChild(padding()
                        ->setPaddings(12, 18)
                        ->setChild(column()
                            ->setSpacing(8)
                            ->appendChild(height()
                                ->setHeight(16)
                                ->setChild(this->activeExampleLabelName))
                            ->appendChild(height()
                                ->setHeight(14)
                                ->setChild(this->activeExampleLabelDescription))))
                    ->appendChild(flexible()
                        ->setChild(this->activeExampleElement)))));
}

void ExamplesGallery::setActiveExample(const std::shared_ptr<Example>& example) {
    this->activeExampleElement
        ->setChild(example->getScene(this->ctx));

    this->activeExampleLabelName
        ->setChild(text()
            ->setFontColor("#062016")
            ->setFontSize(16)
            ->setText(example->getName()));

    this->activeExampleLabelDescription
        ->setChild(text()
            ->setFontColor("#3F4944")
            ->setFontSize(14)
            ->setText(example->getDescription()));
}

std::shared_ptr<Element> ExamplesGallery::makeExamplesList() {
    std::shared_ptr<Column> examplesList = column();
    for (const auto& example : examples()) {
        std::shared_ptr<Background> buttonBackground = background();
        examplesList
            ->appendChild(clickable()
                ->setChild(hoverable()
                    ->setChild(buttonBackground
                        ->setColor("#DEEDE6")
                        ->setChild(padding()
                            ->setPaddings(16, 20)
                            ->setChild(text()
                                ->setFontColor("#006C4C")
                                ->setFontSize(16)
                                ->setFontWeight(450)
                                ->setFontFamily("Fira Code")
                                ->setText(example->getName()))))
                    ->onEnter([buttonBackground] () { buttonBackground->setColor("#C2DDD3"); })
                    ->onLeave([buttonBackground] () { buttonBackground->setColor("#DEEDE6"); }))
                ->onClick([this, example] () { this->setActiveExample(example); }));
    }

    return examplesList;
}
