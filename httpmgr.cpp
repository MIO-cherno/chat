#include "httpmgr.h"

HttpMgr::HttpMgr()
{
    connect(this,&HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);
}

/******************************************************************************
 *  PostHttpReq请求的函数，也就是发送http的post请求, 发送请求要用到请求的url，
 *  请求的数据(json或者protobuf序列化)，以及请求的id，以及哪个模块发出的请求mod，
 *  那么一个请求接口应该是这样的
 *****************************************************************************/
void HttpMgr::postHttpReq(QUrl url, QJsonObject json, ReqId reqId, Modules mod)
{
    //创建一个HTTP POST请求，并设置请求头和请求体
    QByteArray data = QJsonDocument(json).toJson();//将json转化为字节数组（？字节流）
    QNetworkRequest request(url);//通过url构造请求
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");//设置头部，指明请求类型
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));//指明请求长度,自动解决大小端问题
    /******************************************************************************
     *POST /api/user HTTP/1.1
     *Host: example.com
     *Content-Type: application/json
     *Content-Length: 123
     *{
       "name": "John Doe",
       "email": "johndoe@example.com",
       "age": 30
     *}
     *上述代码表示向 example.com 的 /api/user 资源发送一个 POST 请求，
     *请求体中包含了一个 JSON 格式的用户信息。
     *****************************************************************************/

    //发送请求，并处理响应, 通过HttpMgr获取自己的智能指针，构造伪闭包并增加智能指针引用计数
    auto self = shared_from_this();    //丢给lambda表达式，防止lambda没执行完，HttpMgr被析构出现错误
    QNetworkReply * reply = _manger.post(request,data);  //发送请求和请求的内容，得到reply
    //self被lambda表达式捕获，会放到lambda的成员变量里（lambda是一个可调用对象）self引用计数会加一
    //响应reply接收完成后(finished)，执行lambda的操作
    QObject::connect(reply,&QNetworkReply::finished,[self，reply,reqId,mod](){
        //error
        if(reply->error() != QNetworkReply::NoError){
            QDebug<<reply->errorString();
            //发送信号通知完成，告知其他界面
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);

            reply->deleteLater();//不用时回收
            return;
        }

        //无错误则读回请求
        QString res = reply->readAll();

        //发送信号通知完成
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS,mod);
        reply->deleteLater();
        return;
    })



}

//slot_http_finish的槽函数用来接收sig_http_finish信号。
void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if(mod == Modules::REGISTERMOD){
        //发送信号通知指定模块http响应结束
        emit sig_reg_mod_finish(id, res, err);//通知register模块
    }
}

HttpMgr::~HttpMgr()
{

}
