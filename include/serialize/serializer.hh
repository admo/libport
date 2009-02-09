#ifndef LIBPORT_SERIALIZE_SERIALIZER_HH
# define LIBPORT_SERIALIZE_SERIALIZER_HH

# include <vector>

# include <boost/function.hpp>
# include <boost/optional.hpp>

# include <serialize/export.hh>
# include <serialize/fwd.hh>

namespace libport
{
  namespace serialize
  {
    class SERIALIZE_API Serializer
    {
    public:

      Serializer(bool input);
      virtual ~Serializer();

      template <template <typename, typename> class C, typename T, typename A>
      void serialize(const std::string& name, C<T, A>& collection);
      template <typename T>
      void serialize(const std::string& name, boost::optional<T>& option);

      virtual void serialize(const std::string& name, Serializable& s)  = 0;
      virtual void serialize(const std::string& name, std::string& s)   = 0;
      virtual void serialize(const std::string& name, int& i)           = 0;

    protected:
      typedef boost::function0<void> action_type;
      virtual action_type serialize_collection(const std::string& name,
                                               int& size) = 0;
      bool input_;
    };
  }
}

#include <serialize/serializer.hxx>

#endif
