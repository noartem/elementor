//
// Created by noartem on 27.06.2022.
//

#include "utility.h"
#include "DiaryService.h"
#include "DiaryApplication.h"

int main() {
    auto diaryService = std::make_shared<DiaryService>();
    auto diaryApplication = std::make_shared<DiaryApplication>(diaryService);

    auto platform = std::make_shared<GLPlatform>();
    auto window = platform->makeWindow({920, 640});
    window->setTitle("Diary");
    window->setRoot(diaryApplication);
    window->setMinSize({630, 320});
    platform->run();
}