/*
 * A very simple, light-weight object-oriented POSIX thread wrapper.
 * I don't know why I made this.
 *
 * author: valtari
 */

#ifndef LIB_RIBBON_HPP_
#define LIB_RIBBON_HPP_

#include <pthread.h>
#include <unistd.h>

class Runnable {
public:
	Runnable() {};
	virtual ~Runnable() {};
	virtual void run() = 0;
};

class Thread : public Runnable {
private:
	Thread(const Thread&);
	Thread& operator=(const Thread&);

	bool _running;
	pthread_t _tid;

	static void* _exec(void* tmpf) {
		reinterpret_cast<Runnable*> (tmpf)->run();
		return (void*) 0;
	}

	static void* _exec_self(void* tmpf) {
			reinterpret_cast<Thread*> (tmpf)->run();
			return (void*) 0;
		}
public:
	Thread() {
		this->_running = false;
		this->_tid = 0;
	};

	virtual ~Thread() {};
	virtual void run() {};

	int start(Runnable* object) {
		if (_running) return 1;

		int t_error = pthread_create(&_tid, NULL, _exec, object);
		if (t_error != 0) return t_error;
		else return !(_running = true);
	};

	int start() {
		if (_running) return 1;

		int t_error = pthread_create(&_tid, NULL, _exec_self, this);
		if (t_error != 0) return t_error;
		else return !(_running = true);
	}

	void join() {
		if (!_running) return;

		pthread_join(_tid, NULL);
		_running = false;
	};

	unsigned int get_id() const { return _tid; }
	bool is_running() { return _running; }
};

class Mutex {
private:
	Mutex(const Mutex&);
	Mutex operator=(const Mutex&);

	pthread_mutex_t _lock;
public:
	Mutex() { pthread_mutex_init(&_lock, NULL); };
	~Mutex() {}

	void lock() { pthread_mutex_lock(&_lock); }
	void release() { pthread_mutex_unlock(&_lock); };
};

#endif

