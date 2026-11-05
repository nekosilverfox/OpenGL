#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);  // 将 OpenGL 控件作为中央控件充满整个窗口

    connect(ui->actionDrawSphere, &QAction::triggered,
            this, [=](){
                ui->openGLWidget->is_draw_sphere = ui->actionDrawSphere->isChecked();
                ui->openGLWidget->updateGL();
            });

    connect(ui->actionDrawCone, &QAction::triggered,
            this, [=](){
                ui->openGLWidget->is_draw_cone = ui->actionDrawCone->isChecked();
                ui->openGLWidget->updateGL();
            });

    connect(ui->actionDrawCube, &QAction::triggered,
            this, [=](){
                ui->openGLWidget->is_draw_cube = ui->actionDrawCube->isChecked();
                ui->openGLWidget->updateGL();
            });

    connect(ui->actionWireframe, &QAction::triggered,
            this, [=](){
                ui->openGLWidget->setWirefame(ui->actionWireframe->isChecked());
            });  // 如果按下就是线框模式

    connect(ui->actionMoveSphare, &QAction::triggered,
            this, [=](){
                ui->openGLWidget->is_move_sphere = ui->actionMoveSphare->isChecked();
            });

    connect(ui->actionMoveCone, &QAction::triggered,
            this, [=](){
                ui->openGLWidget->is_move_cone = ui->actionMoveCone->isChecked();
            });

    connect(ui->actionMoveCube, &QAction::triggered,
            this, [=](){
                ui->openGLWidget->is_move_cube = ui->actionMoveCube->isChecked();
            });

    connect(ui->actionLightColor, &QAction::triggered,
            this, [=](){
                ui->openGLWidget->is_change_light_color = ui->actionLightColor->isChecked();
            });

}

MainWindow::~MainWindow()
{
    delete ui;
}
