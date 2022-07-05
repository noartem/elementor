//
// Created by noartem on 27.06.2022.
//

#include "utility.h"
#include "DiaryService.h"
#include "DiaryApplication.h"

#include "PageHome.h"
#include "PageTodayEntries.h"
#include "PageTomorrowEntries.h"
#include "PageAllEntries.h"

int main() {
    DiaryService *diaryService = DiaryService::MakeFromFile("diary.csv");
    diaryService->log();

    DiaryApplication *diaryApplication = new DiaryApplication({
        new PageTodayEntries(diaryService),
        new PageTomorrowEntries(diaryService),
        new PageAllEntries(diaryService),
    });
    diaryApplication->setActivePage(new PageHome());

    Application *application = new Application();
    application->root = diaryApplication;

    Platform *platform = new Platform();
    platform->title = "Diary";
    platform->size = {920, 640};
    platform->minSize = {640, 320};
    platform->application = application;

    platform->run();
}