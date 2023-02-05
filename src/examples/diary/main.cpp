//
// Created by noartem on 27.06.2022.
//

#include "utility.h"
#include "DiaryService.h"
#include "DiaryApplication.h"

int main() {
    auto *diaryService = new DiaryService();
    auto *diaryApplication = new DiaryApplication(diaryService);

    auto *platform = new GLPlatform();
    auto *window = platform->makeWindow({920, 640});
    window->setTitle("Diary");
    window->setRoot(diaryApplication->makeElement());
    window->setMinSize({630, 320});
    platform->run();
}