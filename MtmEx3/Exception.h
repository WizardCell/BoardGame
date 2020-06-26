#ifndef HW3_EXCEPTION_H
#define HW3_EXCEPTION_H

#include <exception>

namespace mtm
{
	class Exception : public std::exception {};

	class GameException : public Exception {};
	
	class IllegalArgument : public GameException
	{
		const char* what() const noexcept;
	};

	class IllegalCell : public GameException
	{
		const char* what() const noexcept;
	};

	class CellEmpty : public GameException
	{
		const char* what() const noexcept;
	};

	class MoveTooFar : public GameException
	{
		const char* what() const noexcept;
	};

	class CellOcupied : public GameException
	{
		const char* what() const noexcept;
	};

	class OutOfRange : public GameException
	{
		const char* what() const noexcept;
	};

	class OutOfAmmo : public GameException
	{
		const char* what() const noexcept;
	};

}

#endif
