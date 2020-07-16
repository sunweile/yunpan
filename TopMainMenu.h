#pragma once

#include <QFrame>
#include <QPushButton>
#include <QLabel>

#include "YpButton.h"
#include "VirtualDisk.h"
#include "UserHandle.h"
#include <QResizeEvent>
#pragma execution_character_set("utf-8")
class TopMainMenu : public QFrame
{
	Q_OBJECT

public:
	TopMainMenu(UserHandle* userHandle, QWidget* parent);
	~TopMainMenu();
public slots:
	void ksfwButtonChick();
	void fzButtonChick();
	void ztButtonChick();
	void jqButtonChick();
	void fzljButtonChick();
	void ztkjfsButtonChick();
	void moveToButtonChick();
	void copyToButtonChick();
	void removeButtonChick();
	void renameButtonChick();
	void xwjjButtonChick();
	void xxmButtonChick();
	void qsfwButtonChick();
	void sxButtonChick();
	void openButtonChick();
	void bjButtonChick();
	void lsjlButtonChick();
	void qxButtonChick();
	void qxxzButtonChick();
	void fxButtonChick();
	void ztbButtonChick();
	void zzButtonChick();
	void xjButtonChick();
	void dkButtonChick();
	void xzButtonChick();

public:
	void resizeEvent(QResizeEvent* size);
	void chooseThings(VirtualDisk::fileTree** file,int len);
	void chooseThings(const QStringList& paths);

	void addChooseThing(VirtualDisk::fileTree* file);
	void addChooseThing(const QString& path);

	void removeChooseThing(VirtualDisk::fileTree* file);
	void removeChooseThing(const QString& path);

	void backChooseThings();

	void removeChooseThings();

	void upDate(bool isNow);

	//快速访问
	void ksfwButtonUpDate(int w);
	//复制
	void fzButtonUpDate(int w);
	//粘贴
	void ztButtonUpDate(int w);
	//剪切
	void jqButtonUpDate(int w);
	//复制路径
	void fzljButtonUpDate(int w);
	//粘贴快捷方式
	void ztkjfsButtonUpDate(int w);
	//剪贴板
	void ztbLabelUpDate(int w);

	void ztbButtonUpdate(int w);
	//分割线
	void line1UpDate(int w);

	//移动到
	void moveToButtonUpDate(int w);
	//复制到
	void copyToButtonUpDate(int w);
	//分割线
	void line1_1UpDate(int w);
	//删除
	void removeButtonUpDate(int w);
	//重命名
	void renameButtonUpDate(int w);
	//组织
	void zzLabelUpDate(int w);

	void zzButtonUpdate(int w);
	//分割线
	void line2UpDate(int w);

	//新建文件夹
	void xwjjButtonUpDate(int w);
	//新建项目
	void xxmButtonUpDate(int w);
	//轻松访问
	void qsfwButtonUpDate(int w);
	//新建
	void xjLabelUpDate(int w);

	void xjButtonUpdate(int w);
	//分割线
	void line3UpDate(int w);

	//属性
	void sxButtonUpDate(int w);
	//打开
	void openButtonUpDate(int w);
	//编辑
	void bjButtonUpDate(int w);
	//历史记录
	void lsjlButtonUpDate(int w);
	//打开
	void dkLabelUpDate(int w);

	void dkButtonUpdate(int w);
	//分割线
	void line4UpDate(int w);

	//全选
	void qxButtonUpDate(int w);
	//取消选择
	void qxxzButtonUpDate(int w);
	//反选
	void fxButtonUpDate(int w);
	//选择
	void xzLabelUpDate(int w);

	void xzButtonUpdate(int w);
	//分割线
	void line5UpDate(int w);

private:
	//使用者句柄
	UserHandle* userHandle;

	//快速访问
	YpButton* ksfwButton;
	//复制
	YpButton* fzButton;
	//粘贴
	YpButton* ztButton;
	//剪切
	YpButton* jqButton;
	//复制路径
	YpButton* fzljButton;
	//粘贴快捷方式
	YpButton* ztkjfsButton;
	//剪贴板
	QLabel* ztbLabel;

	YpButton* ztbButton;
	//分割线
	QFrame* line1;

	//移动到
	YpButton* moveToButton;
	//复制到
	YpButton* copyToButton;
	//分割线
	QFrame* line1_1;
	//删除
	YpButton* removeButton;
	//重命名
	YpButton* renameButton;
	//组织
	QLabel* zzLabel;

	YpButton* zzButton;
	//分割线
	QFrame* line2;

	//新建文件夹
	YpButton* xwjjButton;
	//新建项目
	YpButton* xxmButton;
	//轻松访问
	YpButton* qsfwButton;
	//新建
	QLabel* xjLabel;

	YpButton* xjButton;
	//分割线
	QFrame* line3;

	//属性
	YpButton* sxButton;
	//打开
	YpButton* openButton;
	//编辑
	YpButton* bjButton;
	//历史记录
	YpButton* lsjlButton;
	//打开
	QLabel* dkLabel;

	YpButton* dkButton;
	//分割线
	QFrame* line4;

	//全选
	YpButton* qxButton;
	//取消选择
	YpButton* qxxzButton;
	//反选
	YpButton* fxButton;
	//选择
	QLabel* xzLabel;

	YpButton* xzButton;
	//分割线
	QFrame* line5;
};
