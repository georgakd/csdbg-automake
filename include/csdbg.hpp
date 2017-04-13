#ifndef _CSDBG
#define _CSDBG 1

#define _REENTRANT
#define CSDBG_WITH_DEBUG
#define CSDBG_WITHOUT_COLOR_TERM
#define CSDBG_WITH_STREAMBUF
#define CSDBG_WITH_STREAMBUF_FILE
#define CSDBG_WITH_STREAMBUF_TCP
#define CSDBG_WITH_STREAMBUF_STTY
#define CSDBG_WITH_PLUGIN
#define CSDBG_WITH_HIGHLIGHT
#define CSDBG_WITH_FILTER

#include "csdbg/config.hpp"
#include "csdbg/object.hpp"
#include "csdbg/util.hpp"
#include "csdbg/exception.hpp"
#include "csdbg/string.hpp"
#include "csdbg/symbol.hpp"
#include "csdbg/call.hpp"
#include "csdbg/node.hpp"
#include "csdbg/chain.hpp"
#include "csdbg/stack.hpp"
#include "csdbg/symtab.hpp"
#include "csdbg/thread.hpp"
#include "csdbg/process.hpp"
#include "csdbg/tracer.hpp"
#include "csdbg/streambuf.hpp"
#include "csdbg/filebuf.hpp"
#include "csdbg/tcpsockbuf.hpp"
#include "csdbg/sttybuf.hpp"
#include "csdbg/plugin.hpp"
#include "csdbg/style.hpp"
#include "csdbg/dictionary.hpp"
#include "csdbg/parser.hpp"
#include "csdbg/filter.hpp"

#endif

