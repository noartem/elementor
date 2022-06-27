//
// Created by noartem on 27.06.2022.
//

#include "utility.h"
#include "DiaryService.h"
#include "DiaryApplication.h"

#include "PageAllEntries.h"

int main() {
    DiaryService *diaryService = new DiaryService();

    Application *application = new Application();
    application->root = new DiaryApplication({
        new PageAllEntries(diaryService),
    });

    Platform *platform = new Platform();
    platform->title = "Diary";
    platform->size = {920, 640};
    platform->minSize = {640, 320};
    platform->application = application;

    platform->run();
}