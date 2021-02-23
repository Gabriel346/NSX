#include "uveditor.h"
#include "uvviewport.h"

#include <QHBoxLayout>
#include <QPushButton>

UVEditor::UVEditor(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    UVViewport *viewport = new UVViewport(this);
    QSizePolicy policy = viewport->sizePolicy();
   // policy.setVerticalPolicy(QSizePolicy::Maximum);
   // policy.setHorizontalPolicy(QSizePolicy::Maximum);
    viewport->setSizePolicy(policy);

    mainLayout->addWidget(viewport);

//    QPushButton *b = new QPushButton(this);
//    b->setText("aaaaaaaaa");
//    b->setSizePolicy(policy);
//     mainLayout->addWidget(b);

   this->setLayout(mainLayout);
}
