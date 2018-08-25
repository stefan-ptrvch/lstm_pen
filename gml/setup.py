from setuptools import setup, find_packages

# Setup parameters for Google Cloud ML Engine
setup(name="lstm-pencil",
      version="1.7",
      packages=find_packages(),
      include_package_data=True,
      description="Testrun of Keras",
      author="Stefan",
      author_email="petzimir@gmail.com",
      license="MIT",
      install_requires=["keras", "pandas", "scikit-learn", "numpy"],
      zip_safe=False)
