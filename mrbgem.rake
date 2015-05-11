MRuby::Gem::Specification.new 'mruby-glfw3' do |spec|
  spec.authors = ['Corey Powell', 'Takeshi Watanabe']
  spec.license = 'MIT'
  spec.version = '3.1.0.0'
  spec.add_dependency 'mruby-gles', github: 'take-cheeze/mruby-gles', branch: 'glfw3'
  spec.linker.libraries << 'glfw'
end
