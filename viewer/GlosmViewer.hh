/*
 * Copyright (C) 2010-2011 Dmitry Marakasov
 *
 * This file is part of glosm.
 *
 * glosm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * glosm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with glosm.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GLOSMVIEWER_HH
#define GLOSMVIEWER_HH

#include <glosm/FirstPersonViewer.hh>
#include <glosm/GeometryGenerator.hh>
#include <glosm/GeometryLayer.hh>
#include <glosm/PreloadedXmlDatasource.hh>
#include <glosm/Projection.hh>

#include <memory>

#include <sys/time.h>

class GlosmViewer {
public:
	enum Keys {
		UP = 0x100,
		DOWN,
		LEFT,
		RIGHT,
		SHIFT,
		CTRL
	};

protected:
	Projection projection_;
	std::auto_ptr<FirstPersonViewer> viewer_;
	std::auto_ptr<PreloadedXmlDatasource> osm_datasource_;
	std::auto_ptr<GeometryGenerator> geometry_generator_;
	std::auto_ptr<GeometryLayer> geometry_layer_;

	int tile_level_;
	int screenw_;
	int screenh_;

	struct timeval prevtime_, curtime_, fpstime_;
	int nframes_;

	int movementflags_;
	float speed_;
	bool slow_;
	bool fast_;
	int lockheight_;

protected:
	virtual void WarpCursor(int x, int y) = 0;
	virtual void Flip() = 0;

public:
	GlosmViewer();

	virtual void Usage(const char* progname);
	virtual void Init(int argc, char** argv);
	virtual void InitGL();
	virtual void Render();
	virtual void Resize(int w, int h);
	virtual void KeyDown(int key);
	virtual void KeyUp(int key);
	virtual void MouseMove(int x, int y);
};

#endif