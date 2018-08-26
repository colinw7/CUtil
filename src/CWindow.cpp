#include <CWindow.h>
#include <cassert>

static CWindowMgr *s_instance;

CWindowMgr *
CWindowMgr::
instance()
{
  if (! s_instance)
    s_instance = new CWindowMgr;

  return s_instance;
}

void
CWindowMgr::
release()
{
  delete s_instance;

  s_instance = nullptr;
}

CWindowMgr::
CWindowMgr()
{
}

CWindowMgr::
~CWindowMgr()
{
}

void
CWindowMgr::
setFactory(CWindowFactory *factory)
{
  delete factory_;

  factory_ = factory;
}

CWindow *
CWindowMgr::
createWindow(int x, int y, uint width, uint height)
{
  assert(factory_);

  return factory_->createWindow(x, y, width, height);
}

CWindow *
CWindowMgr::
createWindow(CWindow *parent, int x, int y, uint width, uint height)
{
  assert(factory_);

  return factory_->createWindow(parent, x, y, width, height);
}

//-------

CWindow::
CWindow(CWindow *parent) :
 parent_(parent)
{
}

CWindow::
~CWindow()
{
}

void
CWindow::
beep()
{
}
