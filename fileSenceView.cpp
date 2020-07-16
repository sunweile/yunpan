#include "fileSenceView.h"
#include "MainWindows.h"
#include "FileStringTools.h"


#pragma execution_character_set("utf-8")

fileSenceView::fileSenceView(QWidget *parent,QList<VirtualDisk*>* vdl)
	: QWidget(parent)
{
    this->uh = new UserHandle();
    this->vdl = vdl;
    VirtualDisk* vd = vdl->first();
    uh->setVd(vd);
    QString s = "QScrollBar:vertical"
        "{"
        "width:15px;"
        "background:#f0f0f0;"
        "margin:0px,0px,0px,0px;"
        "padding-top:17px;"
        "padding-bottom:17px;"
        "}"
        "QScrollBar::handle:vertical"
        "{"
        "width:15px;"
        "background:#cdcdcd;"
        "min-height:20;"
        "}"
        "QScrollBar::handle:vertical:hover"
        "{"
        "width:15px;"
        "background:#a6a6a6;"
        "min-height:20;"
        "}"
        "QScrollBar::add-line:vertical"
        "{"
        "height:17px;width:15px;"
        "border-image:url(./images/scrollDownBar.png);"
        "subcontrol-position:bottom;"
        "}"
        "QScrollBar::sub-line:vertical"
        "{"
        "height:17px;width:15px;"
        "border-image:url(./images/scrollUpBar.png);"
        "subcontrol-position:top;"
        "}"
        "QScrollBar::add-line:vertical:hover"
        "{"
        "height:17px;width:15px;"
        "border-image:url(./images/scrollDownBarHover.png);"
        "subcontrol-position:bottom;"
        "}"
        "QScrollBar::sub-line:vertical:hover"
        "{"
        "height:17px;width:15px;"
        "border-image:url(./images/scrollUpBarHover.png);"
        "subcontrol-position:top;"
        "}"
        "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
        "{"
        "background:#f0f0f0;"
        "}";
    filesArea = new QScrollArea(this);
    filesArea->setFrameStyle(0);
    filesArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    filesArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    filesArea->setWidgetResizable(true);
    filesArea->setGeometry(204, 7, 600, 200);
    filesArea->verticalScrollBar()->setStyleSheet(s);
    filesArea->show();
    dfv = new DetailedFileView(filesArea,uh);
    dfv->setGeometry(0, 0, 600, 1000);
    dfv->show();
    filesArea->setWidget(dfv);


	scrollArea = new QScrollArea(this);
	scrollArea->setFrameStyle(0);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setWidgetResizable(true);
	scrollArea->setGeometry(0,7,200,200);
    scrollArea->verticalScrollBar()->setStyleSheet(s);
	scrollArea->show();
	fv = new FilesTreeView(scrollArea, vdl);
	fv->upDateWithData();
    fv->setGeometry(0, 0, 400, 800);
    fv->setWidth(400);
    fv->show();

	scrollArea->setWidget(fv);

    line = new YpLine(this);
    lineX = 200;
    line->setGeometry(lineX, 7, 4, 400);
    connect(line, SIGNAL(lineDown(int)), this, SLOT(lineDown(int)));
    connect(line, SIGNAL(lineUp()), this, SLOT(lineUp()));
    connect(line, SIGNAL(lineMove(int)), this, SLOT(lineMove(int)));

    line->setStyleSheet("background-color:#ffffff;border-right:1px solid #f0f0f0;border-left:1px solid #f0f0f0;");
    line->show();

    xm = new QLabel(this);
    xm->setText("0个项目");
    xm->setFont(QFont("微软雅黑", 9, 45));
    xm->setGeometry(10,800,100,25);
    xm->show();

    l1 = new QFrame(this);
    l1->setGeometry(105,800,1,11);
    l1->setStyleSheet("background-color:#f7f7f7;");
    l1->show();

    xmxx = new QLabel(this);
    xmxx->setText("");
    xmxx->setFont(QFont("微软雅黑", 9, 45));
    xmxx->setGeometry(115, 800, 400, 25);
    xmxx->show();

    QFrame* top;

    openDir(vd->getFiles()->getNetPath());

}

fileSenceView::~fileSenceView()
{
}

void fileSenceView::setXm(int i) {
    xm->setText(QString::number(i)+"个项目");
}

void fileSenceView::setXmxx(QList<QString>* cl) {
    if (cl->size() == 0) {
        xmxx->setText("");
    }
    else {
        long long int l = 0;
        for each (QString v in *cl) {
            VirtualDisk::fileTree* f = getUh()->getFiles(v);
            if (f->type == DIR) {
                l = -1;
                break;
            }
            l += f->size;
        }
        if (l == -1) {
            xmxx->setText("已选择" + QString::number(cl->size()) + "个项目");
        }
        else{
            xmxx->setText("已选择" + QString::number(cl->size()) + "个项目，" + FileStringTools::getSize(l));
        }
    }
}

void fileSenceView::openDir(QString path) {
    QStringList pl = path.replace("://", "+:kk:+").split("/");
    path.replace("+:kk:+", "://");
    VirtualDisk* v = NULL;
    for each (VirtualDisk* vd in *(this->vdl)) {
        if (vd->getName() == pl.first().replace("+:kk:+", "://")) {
            v = vd;
            break;
        }
    }
    if (v != NULL) {
        this->getUh()->setVd(v);
        this->getUh()->open(path);
        this->getDfv()->upDate();
        ((MainWindows*)(this->parent()))->getLv()->newPath(path);
        this->xmxx->setText("");
    }
}


void fileSenceView::setSize(int w, int h) {
    this->setFixedHeight(h);
    this->setFixedWidth(w);
    scrollArea->setFixedHeight(h - 31);
    if (scrollArea->height() >= fv->height()) {
        line->setStyleSheet("background-color:#ffffff;border-right:1px solid #f0f0f0;");
    }
    else {
        line->setStyleSheet("background-color:#ffffff;border-right:1px solid #f0f0f0;border-left:1px solid #f0f0f0;");
    }
    line->setFixedHeight(h - 31);
    filesArea->setGeometry(lineX + 4, 7, w - 4 - lineX, h - 31);
    dfv->setFixedWidth(w - 20 - lineX);
    dfv->upDate();
    l1->setGeometry(105, h - 21, 1, 11);
    xm->setGeometry(10, h - 28, 100, 25);
    xmxx->setGeometry(115, h - 28, 400, 25);

}

void fileSenceView::lineDown(int x) {
    posX = x;
}

void fileSenceView::lineUp() {
    this->setCursor(Qt::ArrowCursor);
}

void fileSenceView::lineMove(int x) {
    int dx = x - posX;
    posX = x;
    lineX += dx;
    line->move(lineX, 7);
    scrollArea->setFixedWidth(lineX);
    if (lineX > fv->getWidth()) {
        fv->setWidth(lineX+50);
    }
    filesArea->setGeometry(lineX+4, 7, width()-4-lineX, height()-31);
    
}

DetailedFileView* fileSenceView::getDfv() {
    return dfv;
}

UserHandle* fileSenceView::getUh() {
    return uh;
}

void fileSenceView::setLogin(QStringList sl) {
    QString n = sl[0];
    for each (VirtualDisk* v in *vdl) {
        if (n == v->getDiskName()) {
            v->setLogin(sl);
            break;
        }
    }
}