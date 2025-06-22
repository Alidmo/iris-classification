# src/data_loader.py
from sklearn.datasets import load_iris
import pandas as pd

def load_iris_data() -> pd.DataFrame:
    """
    Load Iris into a DataFrame with 4 feature columns + 'target'.
    """
    iris = load_iris(as_frame=True)
    df = iris.frame.copy()
    # ensure order: features then target
    cols = iris.feature_names + ['target']
    return df[cols]
