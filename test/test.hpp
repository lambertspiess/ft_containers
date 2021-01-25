/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:53:09 by sanam             #+#    #+#             */
/*   Updated: 2020/09/21 17:28:30 by sanam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

#include <iostream>
#include <string>

void title(const std::string& msg);
void red(const std::string& msg);
void blue(const std::string& msg);
void yellow(const std::string &msg);
void cyan(const std::string &msg);
void pink(const std::string& msg);
void white(const std::string& msg);

bool remove_over(int a);
bool uniqueness_sum_under10(int a, int b);
bool comp(int a, int b);

#endif
