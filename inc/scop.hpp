/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:49 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/17 16:50:36 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_HPP
# define SCOP_HPP

# include "utils.hpp"
# include "Shader.hpp"
# include "VAO.hpp"
# include "VBO.hpp"
# include "EBO.hpp"
# include "Texture.hpp"

# define WD_WIDTH 800
# define WD_HEIGHT 800
# define WD_NAME "scop"

class scop {
	public:
		scop(char *filename);
		~scop(void);

		void	setMaterialFilename(str newMaterialFilename);
		void	setName(str newName);
		void	setUsemtl(str newUsemtl);
		void	setSmooth(int newSmooth);

		str			getMaterialFilename(void);
		str			getName(void);
		const int	*getVertices(void);
		const int	*getIndices(void);
		str			getUsemtl(void);
		int			getSmooth(void);

	private:
		str			_materialFilename;
		str			_name;
		const int	*_vertices;
		const int	*_indices;
		str			_usemtl;
		int			_smooth;

};

#endif //SCOP_HPP
