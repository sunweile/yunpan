#include "DetailedFileView.h"
#include "MainWindows.h"

#pragma execution_character_set("utf-8")
DetailedFileView::DetailedFileView(QWidget *parent, UserHandle* uh)
	: QWidget(parent)
{
	showMode = 1;
	files = new QList<FileButton*>();
	chooseList = new QList<QString>();
	useLen = 0;
	this->uh = uh;
	lastUsed = NULL;
	timer = new QTimer(this);
	timer->start(100);
	timeIndex = 0;
	connect(timer, SIGNAL(timeout()), this, SLOT(upDateWithData()));
	searchList = NULL;
}

DetailedFileView::~DetailedFileView()
{
}

void DetailedFileView::upDateWithData() {
	timeIndex++;	

	if (timeIndex == 8) {
		timeIndex = 0;
		if (!uh->upDate() && searchList == NULL) {
			upDate();
		}
	}
	if (searchList != NULL) {
		upDateSearch();
	}
}

void DetailedFileView::upDateSearch() {
	if (uh == NULL) { return; }
	if (files == NULL) {
		files = new QList<FileButton*>();
	}
	useLen = searchIndex;
	if (useLen == 0) {
		for (FileButton* f : *files) {
			f->hide();
		}
	}
	int w = width() - 40;
	int w1 = 271;

	switch (showMode) {
	case 0: {
		w1 = 271;
	}break;
	case 1: {
		w1 = this->width() - 40;
	}break;
	case 2: {
		w1 = 308;
	}break;
	case 3: {

	}break;
	case 4: {
		w1 = 308;
	}break;
	default:
		break;
	}
	int wt = w / w1;
	int wj = (w - wt * w1) / (wt + 1);
	if (searchIndex == 0) {
		search_x = 0;
		search_y = 0;
		search_h = 0;
	}
	for (int i = searchIndex; i < searchList->size(); i++) {
		searchIndex++;
		if (i == files->size()) {
			files->push_back(new FileButton(this));
		}
		int h_ = files->at(i)->setFile(searchList->at(i), showMode);
		if (h_ > search_h) { search_h = h_; }
		files->at(i)->setGeometry((search_x + 1) * wj + search_x * w1 + 20, search_y, w1, h_);
		files->at(i)->show();
		useLen++;
		search_x++;
		if (search_x == wt) {
			search_y += search_h;
			search_x = 0;
			search_h = 0;
		}
	}
	this->setFixedHeight(search_y + search_h);
	lastW = width();
	lastH = height();
	((fileSenceView*)(this->parent()->parent()->parent()))->setXm(useLen);

}

void DetailedFileView::upDate() {
	if (searchList != NULL) {
		search_x = 0;
		search_y = 0;
		search_h = 0;
		searchIndex = 0;
		upDateSearch();
		return;
	}
	if (uh == NULL) { return; }
	if (files == NULL) {
		files = new QList<FileButton*>();
	}
	if (files->size() > 0 && uh->getFiles()->list != NULL && uh->getFiles()->size > 0 && uh->getFiles()->list[0]->getNetPath() == files->first()->getFile()&& uh->FileLen() == useLen && width() == lastW && height() == lastH) { return; }
	useLen = 0;
	for (FileButton* f : *files) {
		f->hide();
	}
	int w = width()-40;
	int w1 = 271;

	switch (showMode){
	case 0: {
		w1 = 271;
	}break;
	case 1: {
		w1 = this->width()-40;
	}break;
	case 2: {
		w1 = 308;
	}break;
	case 3: {
		
	}break;
	case 4: {
		w1 = 308;
	}break;
	default:
		break;
	}
	int wt = w / w1;
	int wj = (w - wt * w1) / (wt + 1);
	int x = 0;
	int y = 0;
	int h = 0;
	for (int i = 0; i < uh->FileLen(); i++) {
		qDebug() << uh->getFiles()->list[i]->name;
		if (i == files->size()) {
			files->push_back(new FileButton(this));
		}
		int h_ = files->at(i)->setFile(uh->getFiles()->list[i], showMode);
		if (h_ > h) { h = h_; }
		files->at(i)->setGeometry((x + 1) * wj + x * w1 + 20, y, w1, h_);
		files->at(i)->show();
		useLen++;
		x++;
		if (x == wt) {
			y += h;
			x = 0;
			h = 0;
		}
	}
	this->setFixedHeight(y + h);
	lastW = width();
	lastH = height();
	((fileSenceView*)(this->parent()->parent()->parent()))->setXm(useLen);
}

void DetailedFileView::otherUnUse(FileButton* b) {
	for (int i = 0; i < useLen; i++) {
		FileButton* f = files->at(i);
		if (f != b) {
			f->focusOut();
		}
	}
	chooseList->clear();
	chooseList->push_back(b->getFile());
	((fileSenceView*)(this->parent()->parent()->parent()))->setXmxx(chooseList);

}

void DetailedFileView::otherUse(FileButton* b) {
	int open = 0;
	chooseList->clear();
	if (lastUsed == NULL) { open = 3; }
	for (int i = 0; i < useLen; i++) {
		FileButton* f = files->at(i);
		if (f == b || f == lastUsed) {
			if (open == 0) { open = 1; }
			else if (open == 1) {
				open = 2;
				f->choose();
				chooseList->push_back(f->getFile());
				continue;
			}
			else if (open == 3) { 
				open = 4; 
				f->choose();
				chooseList->push_back(f->getFile());
				continue;
			}
		}
		if (open == 1 || open == 3) {
			f->choose();
			chooseList->push_back(f->getFile());
		}
		if ((open > 3) && (f != b && f != lastUsed)) {
			f->focusOutChoose();
		}
		if ((open == 0 || open == 2)&& (f != b && f != lastUsed)) {
			f->focusOutChoose();
		}
	}
	((fileSenceView*)(this->parent()->parent()->parent()))->setXmxx(chooseList);
}
void DetailedFileView::otherUnChoose(FileButton* b) {
	for (int i = 0; i < useLen; i++) {
		FileButton* f = files->at(i);
		if (f != b) {
			f->focusOutChoose();
		}
	}
	chooseList->clear();
	if (b) {
		chooseList->push_back(b->getFile());
	}
}

void DetailedFileView::chooseAll() {
	chooseList->clear();
	for (int i = 0; i < useLen; i++) {
		FileButton* f = files->at(i);
		f->choose();
		chooseList->push_back(f->getFile());
	}
}


UserHandle* DetailedFileView::getUh() {
	return uh;
}

void DetailedFileView::mouseReleaseEvent(QMouseEvent* event) {
	otherUnChoose(NULL);
}

void DetailedFileView::setUsed(FileButton* f) {
	lastUsed = f;
}

QList<QString>* DetailedFileView::getList() {
	return chooseList;
}

bool DetailedFileView::getCopy() {
	return isCopy;
}

void DetailedFileView::setCopy(bool b) {
	isCopy = b;
}

void DetailedFileView::open(QString s) {
	((MainWindows*)(this->parent()->parent()->parent()->parent()))->getLv()->newHistory();
	((fileSenceView*)(this->parent()->parent()->parent()))->openDir(s);
}

void DetailedFileView::search(QList<VirtualDisk::fileTree*>* l) {
	searchList = l;
	searchIndex = 0;
}
void DetailedFileView::notSearch() {
	searchList = NULL;
	searchIndex = 0;
}