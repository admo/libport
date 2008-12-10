// Network API based on boost::asio
#ifndef LIBPORT_ASIO_HH
# define LIBPORT_ASIO_HH

# include <iostream>
# include <boost/asio.hpp>
#ifndef LIBPORT_NO_SSL
# include <boost/asio/ssl.hpp>
#endif
# include <boost/function.hpp>

# include <libport/destructible.hh>
# include <libport/finally.hh>
# include <libport/utime.hh>

namespace libport
{
  class AsioDestructible: public Destructible
  {
    protected:
      virtual void doDestroy();
  };
  /** BaseSocket class.
   *
   * This class has a callback-based API: onReadFunc() and onErrorFunc().
   */
  class BaseSocket: public AsioDestructible
  {
    public:
      virtual ~BaseSocket(){}
      libport::Finally deletor;
      /// Write data asynchronously to the socket.
      virtual void write(const void* data, unsigned int length) = 0;
      /// Alias on write() for API compatibility.
      inline void send(void* addr, int len) {write((const void*)addr, len);}
      /// Alias on close() for API compatibility.
      inline void disconnect() {close();}
      /// Return if the socket is connected to a remote host.
      virtual bool isConnected() = 0;
      /// Disconnect the socket from the remote host.
      virtual void close() = 0;
      /// Callback function called each time new data is available.
      boost::function1<bool, boost::asio::streambuf&> onReadFunc;
      /// Callback function called in case of error on the socket.
      boost::function1<void, boost::system::error_code> onErrorFunc;
  };
  /// Endpoint on an UDP socket.
  class UDPLink
  {
    public:
    virtual ~UDPLink() {}
    virtual void reply(const void* data, int length) = 0;
    inline void reply(const std::string& s) {reply(s.c_str(), s.length());}
  };
  /** Socket class with a higher API.
   *
   */
  class Socket: public AsioDestructible
  {
    public:
      Socket(): base_(0){}
      virtual ~Socket();
      /** Set underlying BaseSocket object, setup its callbacks to call our virtual functions.
       */
      virtual void setBase(BaseSocket*);

      /** Called each time new data is received.
       *   \return the number of bytes used in buffer. The remaining data will
       *   be passed again to this function as soon as at least an extra byte
       *   is available.
       */
      virtual int onRead(const void*, int length){return length;}

      /** Called in case of error on the socket.
      */
      virtual void onError(boost::system::error_code){}

      /// Ask for the asynchronous destruction of this object.
      virtual void destroy();

      inline void write(const void* data, unsigned int length)
      { base_->write(data, length);}
      /// Alias on write() for API compatibility.
      inline void send(void* addr, int len) {write((const void*)addr, len);}
      inline void send(const std::string& s) {write(s.c_str(), s.length());}
      inline void close() {if (base_) base_->close();}
      inline bool isConnected() {return base_?base_->isConnected():false;}

      boost::system::error_code connect(const std::string& host,
	  const std::string& port, bool udp=false, utime_t usTimeout = 0);

      typedef void* Handle;
      typedef boost::function0<Socket*> SocketFactory;
      /** Listen using udp.
        * Call onRead(data, length, link) for each new packet. Link can be used
        * to reply to the sender.
        */
      static Handle listenUDP(const std::string& host, const std::string& port,
                  boost::function3<void, const void*, int,
                  boost::shared_ptr<UDPLink> > onRead);
      static Handle listen(SocketFactory f, const std::string& host,
	  const std::string& port, boost::system::error_code & erc,
          bool udp = false);
#ifndef LIBPORT_NO_SSL
      static Handle listenSSL(SocketFactory f, const std::string& host,
	  const std::string&  port,
	  boost::system::error_code& erc,
	  boost::asio::ssl::context_base::method ctx
	    = boost::asio::ssl::context::sslv23_server,
	  boost::asio::ssl::context::options options
	    = boost::asio::ssl::context::verify_none,
	  const std::string& privateKeyFile = "",
	  const std::string& certChainFile = "",
	  const std::string& tmpDHFile = "" ,
	  const std::string& cipherList = "");
#endif
    protected:
      bool onRead_(boost::asio::streambuf&);
      std::string buffer;
      BaseSocket* base_;
    private:
    template<typename Proto, typename BaseFactory> static boost::system::error_code
      listenProto(SocketFactory f, const std::string& host,
	  const std::string&port, BaseFactory bf);
    template<typename Proto, typename BaseFactory> boost::system::error_code
      connectProto(const std::string& host, const std::string& port,
                   utime_t timeout, BaseFactory bf);
  };

  //FIXME: extend to provide a way to ensure workerThread not started.
  /** Get the io_service handling all asynchronous operations.
    *
    * \param startWorkerThread create a thread in which to run the io_service.
    * If \b startWorkerThread is false on \b first invocation, the user
    * is responsible for calling the work or poll methods of the io_service.
    */
  boost::asio::io_service& get_io_service(bool startWorkerThread = true);
}

# include "libport/asio.hxx"

#endif
