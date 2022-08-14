//
// Created by noartem on 27.06.2022.
//

#include "utility.h"
#include "DiaryService.h"
#include "DiaryApplication.h"

int main() {
    DiaryService *diaryService = new DiaryService();
    DiaryApplication *diaryApplication = new DiaryApplication(diaryService);

    GLApplication *application = new GLApplication();
    GLWindow *window = application->makeWindow();
    window->setTitle("Diary");
    window->setRoot(diaryApplication->makeElement());
    window->setSize({920, 640});
    window->setMinSize({630, 320});
    application->run();
}