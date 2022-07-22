//
// Created by noartem on 27.06.2022.
//

#include "utility.h"
#include "DiaryService.h"
#include "DiaryApplication.h"

int main() {
    DiaryService *diaryService = new DiaryService();
    DiaryApplication *diaryApplication = new DiaryApplication(diaryService);

    Application *application = new Application();
    application->root = diaryApplication->makeElement();

    GLPlatform *platform = new GLPlatform();
    platform->title = "Diary";
    platform->size = {920, 640};
    platform->minSize = {640, 320};
    platform->application = application;

    platform->run();
}