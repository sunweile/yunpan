#pragma once

#include <QWebEngineView>
#include "curl/curl.h"
#include "BaiDuClient.h"
#pragma execution_character_set("utf-8")
class WebView : public QWebEngineView
{
	Q_OBJECT

public:
	WebView(QWidget* parent);
	~WebView();
	QString ac;
	QString rc;
	QString code;
	CURL* get;

	void setJs(QString);
	void upDateHandle();
	void slog_cookieAdded(const QNetworkCookie& cookie);
private:
	BaiDuClient* client;
public slots:
	void doSuccess(bool);
	
};
