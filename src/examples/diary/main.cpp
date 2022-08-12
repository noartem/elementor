//
// Created by noartem on 27.06.2022.
//

#include "utility.h"
#include "DiaryService.h"
#include "DiaryApplication.h"

int main() {
    DiaryService *diaryService = new DiaryService();
    DiaryApplication *diaryApplication = new DiaryApplication(diaryService);

    glApplication()
        ->setTitle("Diary")
        ->setRoot(diaryApplication->makeElement())
        ->setDefaultSize({920, 640})
        ->setMinSize({630, 320})
        ->run();
}