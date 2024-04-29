// #include "utility.h"

// namespace PrinterImpl {

// template<typename T>
// String to_string(T data) {
//   return String(data);
// }

// template<>
// String to_string<bool>(bool data) {
//   return data ? "true" : "false";
// }

// template<>
// String to_string<FixedSize>(FixedSize data) {
//   String s;
//   for (auto i = data.data.length(); i < data.size; ++i)
//     s += ' ';
//   s += data.data;
//   return s;
// }

// }