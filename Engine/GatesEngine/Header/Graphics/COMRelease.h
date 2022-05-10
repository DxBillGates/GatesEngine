#pragma once

namespace GE
{
#define COM_RELEASE(p){if((p))p->Release();(p)=nullptr;}
}