#include <thread_pool.h>

#define THREAD_NUM 4

CustomThreadPool::CustomThreadPool()
    : stopFlag_( false )
    , joiner_( threads_ )
{
    // DEBUG( "CustomThreadPool ctor" );
    const auto threadsCount = static_cast<uint32_t>( THREAD_NUM );
    // DEBUG( "Num threads = {}", threadsCount );
    try
    {
        // Инициализация worker потоков
        threads_.reserve( threadsCount );
        for ( uint32_t i = 0; i < threads_.capacity(); ++i )
        {
            threads_.emplace_back( &CustomThreadPool::WorkerThread, this );
        }
    }
    catch ( std::exception& ex )
    {
        // ERROR( "Can't init ThreadPool, error: {}", ex.what() );
        stopFlag_ = true;
        // Пробросить исключение выше
        throw;
    }
}

CustomThreadPool::~CustomThreadPool()
{
    // DEBUG( "CustomThreadPool dtor" );
    stopFlag_ = true;
    condVar.notify_all();
}

void CustomThreadPool::Pause()
{
    workPaused_ = true;
    condVar.notify_all();
}

void CustomThreadPool::Resume()
{
    workPaused_ = false;
    condVar.notify_all();
}

void CustomThreadPool::WorkerThread()
{
    while ( true )
    {
        // TODO: Можно перенести после попытки взять таску, так мы точно возьмем что нибудь до того как вызовется dtor
        // if ( stopFlag_ ) // TODO: Нужно подумать, так ли нам важно что бы при закрытие доделались все таски в очереди
        //  TODO stopFlag_.load() ?
        if ( workPaused_ )
        {
            std::unique_lock lock( mutex_ );
            condVar.wait( lock, [this]() { return stopFlag_ || !workPaused_; } );
        }
        if ( stopFlag_ && workQueue_.IsEmpty() )
        {
            break;
        }

        ThreadTask task;
        if ( workQueue_.TryPop( task ) )
        {
            task();
        }
        else
        {
            // Возвращаем выделенное время в систему
            // Если мы поделилилсь временем то в след раз приоритет на выполнение
            // Данного потока будет выше для системы
            std::this_thread::yield();
        }
    }
    // WARNING( "WorkerThread STOPPED" );
}
