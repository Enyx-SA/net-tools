#include "Error.hpp"

namespace enyx {
namespace tcp_tester {

namespace {

struct category : boost::system::error_category
{
    category()
        : boost::system::error_category()
    { }

    virtual const char*
    name() const
    {
        return "tcp_tester";
    }

    virtual std::string
    message(int condition) const
    {
        switch (condition)
        {
        case error::success: return "Success";
        case error::generic_fault: return "Generic fault";
        case error::unexpected_eof: return "Unexpected Eof";
        case error::checksum_failed: return "Checksum failed";
        case error::test_timeout: return "Test timeout";
        case error::unexpected_data: return "Unexpected data";
        default: return "Unknown error";
        }
    }
};

} // anonymous namespace

const boost::system::error_category &
tcp_tester_category()
{
    static const category c;
    return c;
}

namespace error {

boost::system::error_code
make_error_code(Error e)
{ return boost::system::error_code(e, tcp_tester_category()); }

} // namespace error

} // namespace tcp_tester
} // namespace enyx

