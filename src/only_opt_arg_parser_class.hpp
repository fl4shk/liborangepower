#include "misc/misc_includes.hpp"
#include "strings/sconcat_etc.hpp"

namespace liborangepower {

template<size_t n>
class OnlyOptArgName final {
public:     // variables
    static constexpr size_t size = n;
    char val[n];
    consteval OnlyOptArgName(const char (&str)[n]) {
        std::copy_n(str, n, val);
    }
};

template<
    OnlyOptArgName _name,
    typename OnlyOptArgT,
    bool _takes_val
>
class OnlyOptArg final {
public:     // variables and constants
    static constexpr const char* name = _name.val;
    static constexpr bool takes_val = _takes_val;
    std::optional<OnlyOptArgT> val = std::nullopt;
};

template<typename T>
concept OnlyOptArgTypeConcept = (
    requires(T arg) {
        { arg } -> std::convertible_to<size_t>;
    }
    || requires(T arg) {
        { arg } -> std::convertible_to<const char*>;
    }
    || requires(T arg) {
        { arg } -> std::convertible_to<std::string>;
    }

);

template<typename T>
concept OnlyOptArgConcept = requires(T x) {
    { x.name } -> std::convertible_to<const char*>;
    { static_cast<bool>(x.val) } -> std::convertible_to<bool>;
    { *x.val } -> OnlyOptArgTypeConcept;
    { x.takes_val } -> std::convertible_to<bool>;
};

template<OnlyOptArgConcept... OnlyOptArgTs>
class OnlyOptArgParser final {
private:     // variables and constants
    std::tuple<OnlyOptArgTs...> _args;
public:     // functions
    OnlyOptArgParser() = default;
    OnlyOptArgParser(int argc, char** argv, size_t shift=1) {
        if (int(shift) >= argc) {
            return;
        }
        for (int i=shift; i<argc; ++i) {
            const auto start_i = i;
            const std::string_view arge = argv[i];
            if (arge.size() == 0) {
                continue;
            }

            bool found_named_arg = false;
            auto do_err = [&](
                const std::string& start_msg=(
                    "couldn't parse "
                )
            ) -> void {
                printerr(
                    "Error: ",
                    start_msg,
                    "command line argument at position ", start_i, ": ",
                    arge,
                    "\n",
                    usage_msg()
                );
                std::exit(1);
            };
            std::vector<std::string> my_split_vec;

            for (const auto item: std::views::split(arge, '=')) {
                my_split_vec.push_back(
                    std::string(std::string_view(item))
                );
            }

            template for (auto& arg: _args) {
                if (!found_named_arg) {
                    const std::string_view name = arg.name;
                    using std::operator""sv;
                    if (my_split_vec.front() == name) {
                        found_named_arg = true;
                        auto handle_arg_val_final = [&]() -> void {
                            if (bool(arg.val)) {
                                do_err("duplicate ");
                            }
                            if constexpr (
                                std::convertible_to<
                                    decltype(*arg.val), size_t
                                >
                            ) {
                                arg.val = (
                                    size_t(std::atoll(
                                        my_split_vec.back().c_str()
                                    ))
                                );
                            } else if constexpr (
                                std::convertible_to<
                                    decltype(*arg.val), std::string
                                >
                            ) {
                                arg.val = (
                                    std::string(
                                        my_split_vec.back()
                                    )
                                );
                            } else {
                                static_assert(false);
                            }
                        };

                        if (
                            my_split_vec.size() == 2
                            && arg.takes_val
                        ) {
                            handle_arg_val_final();
                        } else if (
                            my_split_vec.size() == 1
                            && arg.takes_val
                        ) {
                            if (i + 1 >= argc) {
                                do_err();
                            }
                            ++i;
                            my_split_vec.push_back(
                                std::string(std::string_view(argv[i]))
                            );
                            handle_arg_val_final();
                        } else if (
                            my_split_vec.size() == 1
                            && !arg.takes_val
                        ) {
                            if (bool(arg.val)) {
                                do_err("duplicate ");
                            }
                            //arg.val = decltype(*arg.val)();

                            if constexpr (
                                std::convertible_to<
                                    decltype(*arg.val), size_t
                                >
                            ) {
                                arg.val = size_t();
                            } else if constexpr (
                                std::convertible_to<
                                    decltype(*arg.val), std::string
                                >
                            ) {
                                arg.val = std::string();
                            } else {
                                static_assert(false);
                            }
                        } else {
                            printout(
                                "my_split_vec.size() "
                                "== ",
                                my_split_vec.size(),
                                ": ",
                                name, " ", arge, "\n"
                                " (error!)\n"
                            );
                            do_err();
                        }
                    }
                }
            }
            if (!found_named_arg) {
                do_err("invalid ");
            }
        }
    }
    ~OnlyOptArgParser() = default;
    constexpr std::string usage_msg() const {
        std::string ret;
        ret += "Valid arguments are:";

        template for (const auto& arg: _args) {
            ret += sconcat(
                " ", arg.name, ":"
            );
            if constexpr (
                std::convertible_to<decltype(*arg.val), size_t>
            ) {
                ret += "uint";
            } else if constexpr (
                std::convertible_to<decltype(*arg.val), std::string>
            ) {
                ret += "string";
            } else {
                static_assert(false);
            }
        }
        ret += "\n";
        return ret;
    }
    const std::tuple<OnlyOptArgTs...>& args() const {
        return _args;
    }

    template<OnlyOptArgName name, typename T>
    const std::optional<T> find() const {
        template for (const auto& arg: _args) {
            if constexpr (
                std::convertible_to<T, decltype(*arg.val)>
            ) {
                if (
                    arg.name == name.val
                    && arg.val
                ) {
                    return T(*arg.val);
                }
            }
        }
        return std::nullopt;
    }
};

} // namespace liborangepower
