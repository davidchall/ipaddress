#include "IpAddressVector.hpp"

IpAddressVector::IpAddressVector(CharacterVector x)
{
  address.assign(x.size(), asio::ip::address_v4());
  is_na.assign(x.size(), 0);

  CharacterVector::iterator it_input;
  std::vector<asio::ip::address_v4>::iterator it_addr;
  std::vector<bool>::iterator it_na;

  asio::error_code ec;

  for (it_input = x.begin(), it_addr = address.begin(), it_na = is_na.begin();
       it_input != x.end();
       ++it_input, ++it_addr, ++it_na) {
    if (*it_input == NA_STRING) {
      *it_na = true;
    } else {
      *it_addr = asio::ip::make_address_v4(*it_input, ec);
      if (ec) {
        *it_na = true;
        warning(ec.message() + ": " + *it_input);
      }
    }
  }
}

IpAddressVector::IpAddressVector(IntegerVector x)
{
  address.assign(x.size(), asio::ip::address_v4());
  is_na.assign(x.size(), 0);

  IntegerVector::iterator it_input;
  std::vector<asio::ip::address_v4>::iterator it_addr;
  std::vector<bool>::iterator it_na;

  for (it_input = x.begin(), it_addr = address.begin(), it_na = is_na.begin();
       it_input != x.end();
       ++it_input, ++it_addr, ++it_na) {
    if (*it_input == NA_INTEGER) {
      *it_na = true;
    } else {
      *it_addr = asio::ip::make_address_v4((unsigned int)*it_input);
    }
  }
}

IntegerVector IpAddressVector::toIntegerVector() const
{
  IntegerVector output(address.size());

  IntegerVector::iterator it_output;
  std::vector<asio::ip::address_v4>::const_iterator it_addr;
  std::vector<bool>::const_iterator it_na;

  for (it_output = output.begin(), it_addr = address.begin(), it_na = is_na.begin();
       it_output != output.end();
       ++it_output, ++it_addr, ++it_na) {
    if (*it_na) {
      *it_output = NA_INTEGER;
    } else {
      *it_output = (signed int)it_addr->to_uint();
    }
  }

  return output;
}

CharacterVector IpAddressVector::toCharacterVector() const
{
  CharacterVector output(address.size());

  CharacterVector::iterator it_output;
  std::vector<asio::ip::address_v4>::const_iterator it_addr;
  std::vector<bool>::const_iterator it_na;

  for (it_output = output.begin(), it_addr = address.begin(), it_na = is_na.begin();
       it_output != output.end();
       ++it_output, ++it_addr, ++it_na) {
    if (*it_na) {
      *it_output = NA_STRING;
    } else {
      *it_output = it_addr->to_string();
    }
  }

  return output;
}
