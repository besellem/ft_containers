# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/26 17:29:12 by besellem          #+#    #+#              #
#    Updated: 2021/09/26 17:31:44 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

clang++ _test_vector.cpp -DSTD > real
clang++ _test_vector.cpp > mine
diff real mine >> deep
rm real mine
