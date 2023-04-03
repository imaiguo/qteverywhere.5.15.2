#include <QApplication>
#include <QWebEngineView>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <iostream>

QUrl commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
    for (const QString &arg : args.mid(1)) {
        if (!arg.startsWith(QLatin1Char('-')))
            return QUrl::fromUserInput(arg);
    }
    return QUrl(QStringLiteral("https://www.sina.com.cn"));
}


bool OGLSupports(int major, int minor, bool gles = false, QSurfaceFormat::OpenGLContextProfile profile = QSurfaceFormat::NoProfile)
{
    QOpenGLContext ctx;
    QSurfaceFormat fmt;
    fmt.setVersion(major, minor);
    if (gles) {
        fmt.setRenderableType(QSurfaceFormat::OpenGLES);
    } else {
        fmt.setRenderableType(QSurfaceFormat::OpenGL);
        fmt.setProfile(profile);
    }

    ctx.setFormat(fmt);
    ctx.create();
    if (!ctx.isValid())
        return false;
    int ctxMajor = ctx.format().majorVersion();
    int ctxMinor = ctx.format().minorVersion();
    // std::cout<<"Major["<<ctxMajor<<"]"<<"ctxMinor["<<ctxMinor<<"]"<<std::endl;
    bool isGles = (ctx.format().renderableType() == QSurfaceFormat::OpenGLES);

    if (isGles != gles) return false;
    if (ctxMajor < major) return false;
    if (ctxMajor == major && ctxMinor < minor)
        return false;
    if (!gles && ctx.format().profile() != profile)
        return false;
    return true;
}


void printSupport()
{
    std::cout<< "Support for GL 2.0 noprof "<<( OGLSupports(2,0,false) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 2.0 core   "<<( OGLSupports(2,0,false, QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 2.0 compat "<<( OGLSupports(2,0,false, QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 2.1 noprof "<<( OGLSupports(2,1,false) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 2.1 core   "<<( OGLSupports(2,1,false, QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 2.1 compat "<<( OGLSupports(2,1,false, QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 3.0 noprof "<<( OGLSupports(3,0,false) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 3.0 core   "<<( OGLSupports(3,0,false, QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 3.0 compat "<<( OGLSupports(3,0,false, QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout << "Support for GL 3.1 noprof "<<( OGLSupports(3,1,false) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 3.1 core   "<<( OGLSupports(3,1,false, QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 3.1 compat "<<( OGLSupports(3,1,false, QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 3.2 core   "<<( OGLSupports(3,2,false,QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 3.2 compat "<<( OGLSupports(3,2,false,QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 3.3 core   "<<( OGLSupports(3,3,false,QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 3.3 compat "<<( OGLSupports(3,3,false,QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 4.0 core   "<<( OGLSupports(4,0,false,QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 4.0 compat "<<( OGLSupports(4,0,false,QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 4.1 core   "<<( OGLSupports(4,1,false,QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout << "Support for GL 4.1 compat "<<( OGLSupports(4,1,false,QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 4.2 core   "<<( OGLSupports(4,2,false,QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 4.2 compat "<<( OGLSupports(4,2,false,QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 4.3 core   "<<( OGLSupports(4,3,false,QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 4.3 compat "<<( OGLSupports(4,3,false,QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 4.4 core   "<<( OGLSupports(4,4,false,QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 4.4 compat "<<( OGLSupports(4,4,false,QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout << "Support for GL 4.5 core   "<<( OGLSupports(4,5,false,QSurfaceFormat::CoreProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GL 4.5 compat "<<( OGLSupports(4,5,false,QSurfaceFormat::CompatibilityProfile) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GLES 2.0 "<<( OGLSupports(2,0,true) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GLES 3.0 "<<( OGLSupports(3,0,true) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GLES 3.1 "<<( OGLSupports(3,1,true) ? "yes" : "no")<<std::endl;
    std::cout<< "Support for GLES 3.2 "<<( OGLSupports(3,2,true) ? "yes" : "no")<<std::endl;
}


bool isSupportOpenGL()
{
    QOpenGLContext ctx;
    QSurfaceFormat fmt;
    fmt.setRenderableType(QSurfaceFormat::OpenGL);
    ctx.setFormat(fmt);
    if(!ctx.create())
        return false;
    if (!ctx.isValid())
        return false;

    return (ctx.format().renderableType() == QSurfaceFormat::OpenGL);
}

bool isSupportOpenGLES()
{
    QOpenGLContext ctx;
    QSurfaceFormat fmt;
    fmt.setRenderableType(QSurfaceFormat::OpenGLES);
    ctx.setFormat(fmt);
    if(!ctx.create())
        return false;
    if (!ctx.isValid())
        return false;

    return (ctx.format().renderableType() == QSurfaceFormat::OpenGLES);
}

bool setOpenGL()
{
    if(isSupportOpenGL())
    {
        std::cout<<"---SupportOpenGL---"<<std::endl;
        return true;
    }

    if(isSupportOpenGLES())
    {
        std::cout<<"---Support OpenGLES---"<<std::endl;
        return true;
    }

    return false;
}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    printSupport();
    if(!setOpenGL())
    {
        std::cout<<"Error:OpenGL isn't supperted,exit..."<<std::endl;
        return -1;
    }

   if(isSupportOpenGLES())
   {
	qputenv("QT_WAYLAND_SHELL_INTEGRATION", "kwayland-shell");
       QSurfaceFormat format;
       format.setRenderableType(QSurfaceFormat::OpenGLES);
       QSurfaceFormat::setDefaultFormat(format);
   }

    QWebEngineView view;
    view.setUrl(commandLineUrlArgument());
    view.resize(1480, 750);
    view.show();
    return app.exec();
}
