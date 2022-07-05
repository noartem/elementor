//
// Created by noartem on 01.07.2022.
//

#include "PageHome.h"

std::string PageHome::getName() {
    return "Home";
}

Element *PageHome::getScene() {
    return padding()
        ->setPaddings(24, 36)
        ->setChild(column()
            ->setSpacing(4)
            ->appendChild(text()
                ->setFontColor("#2B1615")
                ->setFontFamily("Times New Roman")
                ->setFontSize(36)
                ->setText("Diary application"))
            ->appendChild(height()->setHeight(8))
            ->appendChild(text()
                ->setFontColor("#2B1615")
                ->setFontSize(16)
                ->setText("Author: Noskov Artem"))
            ->appendChild(text()
                ->setFontColor("#2B1615")
                ->setFontSize(16)
                ->setText("Contacts: nowasmawesome@gmail.com"))
            ->appendChild(text()
                ->setFontColor("#2B1615")
                ->setFontSize(16)
                ->setText("Source code: github.com/noartem/elementor")));
}
