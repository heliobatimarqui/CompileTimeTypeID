#include <cstddef>
#include <type_traits>

using id_type = int;
template <typename... Ts> class TypeList;

template <typename... Ts> class HasRepeatedParameter;

template <typename T, typename... Ts> class HasRepeatedParameter<T, T, Ts...> {
public:
  static constexpr bool value = true;
};

template <typename T1, typename T2, typename... Ts> class HasRepeatedParameter<T1, T2, Ts...> {
public:
  static constexpr bool value = HasRepeatedParameter<T1, Ts...>::value || HasRepeatedParameter<T2, Ts...>::value;
};

template <typename T> class HasRepeatedParameter<T> {
public:
  static constexpr bool value = false;
};


template <> class TypeList<> {
public:
    //This will be useful later
    static constexpr id_type id = -1;  
    template <typename T> static constexpr id_type index_of() { return id; }
};

template <typename T, typename... Ts> class TypeList<T, Ts...> {
    // Here we have our check
    static_assert(!HasRepeatedParameter<T, Ts...>::value, "TypeList can't have repeated parameters");

    using remaining_types = TypeList<Ts...>;  
    static constexpr id_type id = sizeof...(Ts);

    template<typename U, bool dummy> 
    struct Helper {
        static constexpr id_type value = remaining_types::template index_of<U>();  
    };

    template<bool dummy>
    struct Helper<T, dummy> {
        static constexpr id_type value = id;
    };

public:

  // Returns -1 when the type is not found
  template <typename F> static constexpr id_type index_of() {
      return Helper<F, true>::value;
  };

};
