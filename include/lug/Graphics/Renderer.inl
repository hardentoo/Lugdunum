inline const Renderer::InitInfo& Renderer::getInfo() const {
    return _initInfo;
}

inline Renderer::Type Renderer::getType() const {
    return _type;
}

inline ResourceManager* Renderer::getResourceManager() const {
    return _resourceManager.get();
}

inline const Renderer::DisplayMode& Renderer::getDisplayMode() const {
    return _displayMode;
}

inline void Renderer::setDisplayMode(Renderer::DisplayMode displayMode) {
    _displayMode = displayMode;
}
