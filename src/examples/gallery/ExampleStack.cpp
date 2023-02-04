//
// Created by noartem on 03.02.2023.
//

#include "ExampleStack.h"

std::string ExampleStack::getName() {
    return "Stack";
}

std::string ExampleStack::getDescription() {
    return "Stack elements one on top of another";
}

Element *stackBasicExample() {
    return width()
        ->setWidth(512)
        ->setChild(height()
            ->setHeight(512)
            ->setChild(stack()
                ->appendChild(center()
                    ->setChild(boxSized("#EDF5F0", 512, 512)))
                ->appendChild(center()
                    ->setChild(boxSized("#CDE8D9", 512, 256)))
                ->appendChild(center()
                    ->setChild(boxSized("#BEE8FA", 128, 192)))
                ->appendChild(center()
                    ->setChild(boxSized("#DEEDE6", 256, 64)))
                ->appendChild(center()
                    ->setChild(rounded()
                        ->setRadius(8)
                        ->setChild(background()
                            ->setColor("#57965C")
                            ->setChild(padding()
                                ->setPaddings(32)
                                ->setChild(text()
                                    ->setFontColor("#FFFFFF")
                                    ->setFontSize(24)
                                    ->setText("Stack child"))))))
                ->appendChild(padding()
                    ->setPaddings(32, 64)
                    ->setChild(rounded()
                        ->setRadius(8)
                        ->setChild(background()
                            ->setColor("#366ACE")
                            ->setChild(padding()
                                ->setPaddings(6, 12, 10, 12)
                                ->setChild(text()
                                    ->setFontColor("#FFFFFF")
                                    ->setFontSize(12)
                                    ->setText("Positioned by padding"))))))));
}

Element *tooltipExample() {
    auto tooltipElement = tooltip();
    return tooltipElement
        ->setChild(hoverable()
            ->setChild(button()
                ->setLabel("Hover me!"))
            ->onEnter([tooltipElement]() { tooltipElement->setActive(true); })
            ->onLeave([tooltipElement]() { tooltipElement->setActive(false); }))
        ->setTip(rounded()
            ->setRadius(8)
            ->setChild(background()
                ->setColor("#366ACE")
                ->setChild(padding()
                    ->setPaddings(6, 12, 10, 12)
                    ->setChild(column()
                        ->setSpacing(4)
                        ->appendChild(text()
                            ->setFontColor("#FFFFFF")
                            ->setFontSize(12)
                            ->setText("Tooltip"))
                        ->appendChild(text()
                            ->setFontColor("#FFFFFF")
                            ->setFontSize(12)
                            ->setText("Blue Tooltip"))
                        ->appendChild(text()
                            ->setFontColor("#FFFFFF")
                            ->setFontSize(12)
                            ->setText("Soooooooooooooooooooooo bbbbbbiiiiiiiiiiiiiiiiiiiig"))
                        ->appendChild(text()
                            ->setFontColor("#FFFFFF")
                            ->setFontSize(12)
                            ->setText("It's Awesome!!!!!"))))));
}

Element *ExampleStack::getScene(ApplicationContext *ctx) {
    return scroll()
        ->setChild(padding()
            ->setPaddings(24, 36)
            ->setChild(column()
                ->setSpacing(24)
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Tooltip"))
                ->appendChild(alignWidth()
                    ->setChild(tooltipExample()))
                ->appendChild(text()
                    ->setFontColor("#062016")
                    ->setFontSize(16)
                    ->setText("Basic"))
                ->appendChild(alignWidth()
                    ->setChild(stackBasicExample()))));
}
