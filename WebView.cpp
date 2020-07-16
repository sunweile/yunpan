#include "WebView.h"
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include "FileStringTools.h"
#include <QJsonDocument>
#include "LoginDialog.h"
#pragma execution_character_set("utf-8")
WebView::WebView(QWidget *parent)
	: QWebEngineView(parent)
{
	//QWebEngineCookieStore* cookie = this->page()->profile()->cookieStore();
	//cookie->deleteAllCookies();
	get = curl_easy_init();
	connect(this->page()->profile()->cookieStore(), &QWebEngineCookieStore::cookieAdded, this, &WebView::slog_cookieAdded);
	this->load(QUrl("https://openapi.baidu.com/oauth/2.0/authorize?response_type=code&client_id=dT3XIFSZU8jK7smucwAuypwe&redirect_uri=oob&scope=basic,netdisk"));
	connect(this, SIGNAL(loadFinished(bool)), this, SLOT(doSuccess(bool)));

}



void WebView::slog_cookieAdded(const QNetworkCookie& cookie)

{
	qDebug() << "Cookie Added-->" << cookie.domain() << cookie.name() << cookie.value() << endl;
}

WebView::~WebView()
{
}

void WebView::setJs(QString) {

}



void WebView::doSuccess(bool b) {
	if (b) {
		this->page()->runJavaScript("(function(){if (document.getElementById(\"Verifier\") != null){return document.getElementById(\"Verifier\").value;}else{return \"no\";}})();", [this](const QVariant& v) {QString s = v.toString(); if (s != "no") {
			this->code = s;
			QString re;
			char urlc[1024];
			FileStringTools::getChar("https://openapi.baidu.com/oauth/2.0/token?grant_type=authorization_code&code="+ code +"&client_id=dT3XIFSZU8jK7smucwAuypwe&client_secret=QsrhuBbz3Um5lbdOG9fnQ2XEwQf5iVfq&redirect_uri=oob&scope=basic,netdisk", urlc);
			curl_easy_setopt(get, CURLOPT_URL, urlc);
			curl_easy_setopt(get, CURLOPT_WRITEDATA, (void*)&re);
			curl_easy_setopt(get, CURLOPT_COOKIEJAR, "D:/cookies.txt");
			curl_easy_setopt(get, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
			int ok = curl_easy_perform(get);
			curl_easy_reset(get);
			QStringList sl;
			if (ok == 0) {
				QJsonDocument json = QJsonDocument::fromJson((re.split("}")[0] + "}").toLatin1());
				if (json["error"].isUndefined()) {
					ac = json["access_token"].toString();
					rc = json["refresh_token"].toString();
					sl.push_back("BAIDU");
					sl.push_back("SUCCESS");
					sl.push_back(ac);
					sl.push_back(rc);
				}
			}
			else {
				sl.push_back("BAIDU");
				sl.push_back("DEFEAT");
			}
			((LoginDialog*)parent())->setStr(sl);
			((LoginDialog*)parent())->close();
		} });
	}
}
