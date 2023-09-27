/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:09:14 by vgroux            #+#    #+#             */
/*   Updated: 2023/09/27 17:06:45 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.class.hpp"

HttpRequest::HttpRequest(void)
{
	// std::cout << "HttpRequest Default constructor called" << std::endl;
	_method_str[::GET] = "GET";
	_method_str[::POST] = "POST";
	_method_str[::DELETE] = "DELETE";
	_method_str[::NONE] = "NONE";
	return ;
}

HttpRequest::HttpRequest(const HttpRequest& src)
{
	// std::cout << "HttpRequest Copy constructor called" << std::endl;
	return ;
}

HttpRequest&	HttpRequest::operator=(const HttpRequest& src)
{
	// std::cout << "HttpRequest Assignement constructor called" << std::endl;
	return *this;
}

HttpRequest::~HttpRequest(void)
{
	// std::cout << "HttpRequest Destructor called" << std::endl;
}

HttpMethod	HttpRequest::getMethod(void) const
{
	return _method;
}

std::string	HttpRequest::getPath(void) const
{
	return _path;
}

void	HttpRequest::parse(char *data, size_t len)
{
	char				c;
	std::stringstream	s;
	short				mi = 1;
	std::string			temp;

	for (size_t i = 0; i < len; i++)
	{
		c = data[i];
		switch(_state)
		{
			case REQUEST_LINE:
			{
				if (c == 'G')
					_method = GET;
				else if (c == 'P')
					_method = POST;
				else if (c == 'D')
					_method = DELETE;
				else
				{
					_err_code = 501;
					std::cerr << "Method Error in REQUEST_LINE. char is: " << c << std::endl;
					return ;
				}
				_state = REQUEST_LINE_METHOD;
				break ;
			}
			case REQUEST_LINE_METHOD:
			{
				if (c == _method_str[_method][mi])
					mi++;
				else
				{
					_err_code = 501;
					std::cerr << "Method Error in REQUEST_LINE_METHOD. char is: " << c << std::endl;
					return ;
				}

				if ((size_t)mi == _method_str[_method].length())
					_state = REQUEST_LINE_SPACE_BEFORE_URI;
				break ;
			}
			case REQUEST_LINE_SPACE_BEFORE_URI:
			{
				if (c != ' ')
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_SPACE_BEFORE_URI)" << std::endl;
					return ;
				}
				_state = REQUEST_LINE_URI_SLASH;
				break ;
			}
			case REQUEST_LINE_URI_SLASH:
			{
				if (c == '/')
				{
					_state = REQUEST_LINE_URI;
					temp.clear();
				}
				else
				{
					_err_code = 400;
					std::cerr << "Bad request (REQUEST_LINE_URI_SLASH)" << std::endl;
				}
				break ;
			}
			case REQUEST_LINE_URI:
			{
				if (c == ' ')
				{
					_path.append(temp);
					temp.clear();
					_state = REQUEST_LINE_SPACE_AFTER_URI;
				}
				else if
				{

				}
			}
			case REQUEST_LINE_SPACE_AFTER_URI:
			{
				if (c == ' ')
					_state = REQUEST_LINE_H;
				else
				{
					_err_code = 400;
					std::cerr << "Bad Request (REQUEST_LINE_SPACE_AFTER_URI)" << std::endl;
					return ;
				}
			}
			case REQUEST_LINE_H:
			{

			}
		}
		temp += c;
		if (_state == PARSING_DONE)
			return ;
	}
}
