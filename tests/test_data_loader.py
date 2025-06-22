# tests/test_data_loader.py
import pandas as pd
from src.data_loader import load_iris_data

def test_load_iris_data():
    df = load_iris_data()
    # 150 samples × 5 cols (4 features + target)
    assert isinstance(df, pd.DataFrame)
    assert df.shape == (150, 5)
    expected = ['sepal length (cm)', 'sepal width (cm)',
                'petal length (cm)', 'petal width (cm)', 'target']
    assert list(df.columns) == expected
    assert set(df['target'].unique()) == {0, 1, 2}
