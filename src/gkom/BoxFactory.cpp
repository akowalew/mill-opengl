#include "gkom/BoxFactory.hpp"

#include "gkom/Logging.hpp"

namespace gkom {

BoxFactory::BoxFactory()
	:	logger_(Logging::getLogger("BoxFactory"))
{
	logger_("Initialized");
}

BoxFactory::~BoxFactory() = default;

Mesh* BoxFactory::createBox(bool withNormals)
{
	if(withNormals)
	{
		return createBoxWithNormals();
	}
	else
	{
		return createBox();
	}
}

Mesh* BoxFactory::createBox()
{
	if(box_)
	{
		logger_("Reusing existing box...");
		return box_.get();
	}

	box_ = std::move(makeBox());
	assert(box_);
	return box_.get();
}

Mesh* BoxFactory::createBoxWithNormals()
{
	if(boxWithNormals_)
	{
		logger_("Reusing existing box with normals...");
		return boxWithNormals_.get();
	}

	boxWithNormals_ = std::move(makeBoxWithNormals());
	assert(boxWithNormals_);
	return boxWithNormals_.get();
}

std::unique_ptr<Mesh> BoxFactory::makeBox()
{
	logger_("Making new box...");

	return std::make_unique<Mesh>(makePositions());
}

std::unique_ptr<Mesh> BoxFactory::makeBoxWithNormals()
{
	logger_("Making new box with normals...");

	const auto indices = std::nullopt;
	return std::make_unique<Mesh>(makePositions(), indices, makeNormals());
}

std::vector<Position> BoxFactory::makePositions()
{
	return {
	    {-0.5f, -0.5f, -0.5f},
	    { 0.5f, -0.5f, -0.5f},
	    { 0.5f,  0.5f, -0.5f},
	    { 0.5f,  0.5f, -0.5f},
	    {-0.5f,  0.5f, -0.5f},
	    {-0.5f, -0.5f, -0.5f},
	    {-0.5f, -0.5f,  0.5f},
	    { 0.5f, -0.5f,  0.5f},
	    { 0.5f,  0.5f,  0.5f},
	    { 0.5f,  0.5f,  0.5f},
	    {-0.5f,  0.5f,  0.5f},
	    {-0.5f, -0.5f,  0.5f},
	    {-0.5f,  0.5f,  0.5f},
	    {-0.5f,  0.5f, -0.5f},
	    {-0.5f, -0.5f, -0.5f},
	    {-0.5f, -0.5f, -0.5f},
	    {-0.5f, -0.5f,  0.5f},
	    {-0.5f,  0.5f,  0.5f},
	    { 0.5f,  0.5f,  0.5f},
	    { 0.5f,  0.5f, -0.5f},
	    { 0.5f, -0.5f, -0.5f},
	    { 0.5f, -0.5f, -0.5f},
	    { 0.5f, -0.5f,  0.5f},
	    { 0.5f,  0.5f,  0.5f},
	    {-0.5f, -0.5f, -0.5f},
	    { 0.5f, -0.5f, -0.5f},
	    { 0.5f, -0.5f,  0.5f},
	    { 0.5f, -0.5f,  0.5f},
	    {-0.5f, -0.5f,  0.5f},
	    {-0.5f, -0.5f, -0.5f},
	    {-0.5f,  0.5f, -0.5f},
	    { 0.5f,  0.5f, -0.5f},
	    { 0.5f,  0.5f,  0.5f},
	    { 0.5f,  0.5f,  0.5f},
	    {-0.5f,  0.5f,  0.5f},
	    {-0.5f,  0.5f, -0.5f},
	};
}

std::vector<Normal> BoxFactory::makeNormals()
{
	return {
		{ 0.0f,  0.0f, -1.0f},
		{ 0.0f,  0.0f, -1.0f},
		{ 0.0f,  0.0f, -1.0f},
		{ 0.0f,  0.0f, -1.0f},
		{ 0.0f,  0.0f, -1.0f},
		{ 0.0f,  0.0f, -1.0f},
		{ 0.0f,  0.0f,  1.0f},
		{ 0.0f,  0.0f,  1.0f},
		{ 0.0f,  0.0f,  1.0f},
		{ 0.0f,  0.0f,  1.0f},
		{ 0.0f,  0.0f,  1.0f},
		{ 0.0f,  0.0f,  1.0f},
		{-1.0f,  0.0f,  0.0f},
		{-1.0f,  0.0f,  0.0f},
		{-1.0f,  0.0f,  0.0f},
		{-1.0f,  0.0f,  0.0f},
		{-1.0f,  0.0f,  0.0f},
		{-1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},
		{ 0.0f, -1.0f,  0.0f},
		{ 0.0f, -1.0f,  0.0f},
		{ 0.0f, -1.0f,  0.0f},
		{ 0.0f, -1.0f,  0.0f},
		{ 0.0f, -1.0f,  0.0f},
		{ 0.0f, -1.0f,  0.0f},
		{ 0.0f,  1.0f,  0.0f},
		{ 0.0f,  1.0f,  0.0f},
		{ 0.0f,  1.0f,  0.0f},
		{ 0.0f,  1.0f,  0.0f},
		{ 0.0f,  1.0f,  0.0f},
		{ 0.0f,  1.0f,  0.0f},
	};
}

} // gkom
